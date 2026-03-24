#!/bin/bash
#
#

set -eu

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
SEL4_PATH="${SEL4_PATH:-$SCRIPT_DIR/build}"
QEMU_CONSOLE="${QEMU_CONSOLE:-vga}"

KERNEL_IMAGE="$SEL4_PATH/images/kernel-x86_64-pc99"
ROOT_IMAGE="$SEL4_PATH/images/sel4benchapp-image-x86_64-pc99"

if [ "$QEMU_CONSOLE" = "serial" ]; then
    exec sudo qemu-system-x86_64         -enable-kvm         -cpu host         -nographic         -serial mon:stdio         -m 512M         -kernel "$KERNEL_IMAGE"         -initrd "$ROOT_IMAGE"
fi

exec sudo qemu-system-x86_64     -enable-kvm     -cpu host     -m 512M     -display curses     -vga std     -serial none     -kernel "$KERNEL_IMAGE"     -initrd "$ROOT_IMAGE"
