         .data
         .text
         .global __start
__start:
         li $4, 0xffffffff
nop
nop
/* mflxc0 $4,$31 */
nop
nop
         li $2, 4001
         syscall
