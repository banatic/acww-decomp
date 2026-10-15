/* func_0204de14 @ 0x0204de14, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02060da8(int arg, int);
extern void func_02037e88(int *object, int value);

extern unsigned char data_021ebcd4[];

// clang-format off
asm int func_0204de14(int *p, int column)
{
    push {r4, lr}
    add r4, r0, #0
    ldr r0, =data_021ebcd4
    bl func_02060da8
    add r1, r0, #0
    ldr r0, [r4]
    cmp r0, #0
    beq done
    bl func_02037e88
done:
    pop {r4}
    pop {r3}
    bx r3
}
// clang-format on
