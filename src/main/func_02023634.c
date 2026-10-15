/* func_02023634 @ 0x02023634, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct Pair {
    int a;
    int b;
} data_020d9090;
extern void func_020157c8(void *p, int a, int b);
extern int func_02015828(void *p, int a);
extern void func_0202dbf0(void *p, struct Pair pair);

// clang-format off
asm int func_02023634(void *arg0)
{
    push {r4, lr}
    add r4, r0, #0
    mov r1, #0x31
    mov r2, #0
    bl func_020157c8
    add r0, r4, #0
    mov r1, #2
    bl func_02015828
    add r0, r4, #0
    ldr r3, =data_020d9090
    ldmia r3!, {r1, r2}
    bl func_0202dbf0
    pop {r4}
    pop {r3}
    bx r3
}
// clang-format on
