// UNSUPPORTED: system-windows
//
// Test that the BareMetal driver auto-links atto_libc_io.o, default linker
// script, -lc and -lm for the attorv32-nano target.
//
// RUN: %clang %s -### --target=riscv32-unknown-elf -o %t.out 2>&1 \
// RUN:     --sysroot=%S/Inputs/attorv32_sysroot/lib/clang-runtimes/riscv32-unknown-elf \
// RUN:   | FileCheck --check-prefix=CHECK-ATTO %s
//
// Verify crt0.o is on the link line
// CHECK-ATTO: "{{[^"]*}}crt0.o"
//
// Verify atto_libc_io.o is auto-linked
// CHECK-ATTO-SAME: "{{[^"]*}}atto_libc_io.o"
//
// Verify default linker script is auto-added (no user -T)
// CHECK-ATTO-SAME: "-T{{[^"]*}}link.ld"
//
// Verify -lc and -lm are both present
// CHECK-ATTO-SAME: "-lc"
// CHECK-ATTO-SAME: "-lm"
//
// Now verify that a user-supplied -T suppresses the default link.ld
//
// RUN: %clang %s -### --target=riscv32-unknown-elf -o %t.out 2>&1 \
// RUN:     --sysroot=%S/Inputs/attorv32_sysroot/lib/clang-runtimes/riscv32-unknown-elf \
// RUN:     -T custom.ld \
// RUN:   | FileCheck --check-prefix=CHECK-CUSTOM-LD %s
//
// CHECK-CUSTOM-LD: "-T" "custom.ld"
// CHECK-CUSTOM-LD-NOT: "-T{{[^"]*}}link.ld"
//
// Verify -nostdlib suppresses crt0.o, atto_libc_io.o, -lc, -lm
//
// RUN: %clang %s -### --target=riscv32-unknown-elf -nostdlib -o %t.out 2>&1 \
// RUN:     --sysroot=%S/Inputs/attorv32_sysroot/lib/clang-runtimes/riscv32-unknown-elf \
// RUN:   | FileCheck --check-prefix=CHECK-NOSTDLIB %s
//
// CHECK-NOSTDLIB-NOT: "crt0.o"
// CHECK-NOSTDLIB-NOT: "atto_libc_io.o"
// CHECK-NOSTDLIB-NOT: "-lc"
// CHECK-NOSTDLIB-NOT: "-lm"

int main(void) { return 0; }
