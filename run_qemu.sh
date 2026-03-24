#!/bin/bash
#
#

SEL4_PATH=$HOME/sel4bench/build/

sudo qemu-system-x86_64 -enable-kvm -cpu host -nographic -serial mon:stdio -m 512M -kernel $SEL4_PATH/images/kernel-x86_64-pc99 -initrd $SEL4_PATH/images/sel4benchapp-image-x86_64-pc99
