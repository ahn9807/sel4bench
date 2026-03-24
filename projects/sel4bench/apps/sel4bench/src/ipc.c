/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
#include <autoconf.h>
#include <ipc.h>
#include <jansson.h>
#include <sel4bench/sel4bench.h>
#include <utils/util.h>

#include "benchmark.h"
#include "math.h"
#include "printing.h"
#include "processing.h"

static json_t *process_ipc_results(void *r)
{
    ipc_results_t *raw_results = r;
    ccnt_t overheads[NUM_OVERHEAD_BENCHMARKS];

    /* check overheads */
    for (int i = 0; i < NUM_OVERHEAD_BENCHMARKS; i++) {
        if (!results_stable(&raw_results->overhead_benchmarks[i][1], RUNS - 1)) {
            if (!config_set(CONFIG_ALLOW_UNSTABLE_OVERHEAD)) {
                printf("Benchmarking overhead of a %s is not stable! Cannot continue\n",
                       overhead_benchmark_params[i].name);
                print_all(RUNS, raw_results->overhead_benchmarks[i]);
                return NULL;
            }
        }
        result_desc_t desc = {
            .stable = false,
            .name = "overhead",
            .ignored = 0,
            .overhead = 0
        };
        result_t overhead_result;
        overhead_result = process_result(RUNS - 1, raw_results->overhead_benchmarks[i], desc);
        overheads[i] = overhead_result.min;
    }

    int n = ARRAY_SIZE(benchmark_params);

    printf("function,direction,same_vspace,length,avg_cycles,std_cycles,n\n");
    for (int i = 0; i < n; i++) {
        result_desc_t desc = {
            .name = benchmark_params[i].name,
            .overhead = overheads[benchmark_params[i].overhead_id],
        };
        result_t result = process_result(RUNS, raw_results->benchmarks[i], desc);
        const char *direction = benchmark_params[i].direction == DIR_TO ? "client->server" :
                                "server->client";

        printf("%s,%s,%s,%u,%.2f,%.2f,%zu\n",
               benchmark_params[i].name,
               direction,
               benchmark_params[i].same_vspace ? "yes" : "no",
               benchmark_params[i].length,
               result.mean,
               result.stddev,
               result.samples);
    }

    return json_array();
}

static benchmark_t ipc_benchmark = {
    .name = "ipc",
    .enabled = config_set(CONFIG_APP_IPCBENCH),
    .results_pages = BYTES_TO_SIZE_BITS_PAGES(sizeof(ipc_results_t), seL4_PageBits),
    .process = process_ipc_results,
    .init = blank_init
};

benchmark_t *ipc_benchmark_new(void)
{
    return &ipc_benchmark;
}
