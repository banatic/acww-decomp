/* func_0201d398 @ 0x0201d398, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void);
extern unsigned char *func_020992e4(void *p);
extern unsigned char func_02082274(unsigned char a, unsigned char b);
extern void func_02015ed0(void *p, unsigned char b, int c);
extern void func_02015ea0(void *p, unsigned char b, int c);
extern int func_02015dd4(void *p, int a, void *b, void *c);
extern char data_020d9f48;

void func_0201d398(void *arg0)
{
    unsigned char *q;
    unsigned char x;
    struct {
        void *reserved;
        unsigned char bytes[2];
    } call_space;

    q = func_020992e4(func_020984e8());
    x = func_02082274(q[1], q[0]);
    func_02015ed0(arg0, q[1], 0);
    func_02015ea0(arg0, q[0], 1);
    // clang-format off
    asm {
        add r0, sp, #4
        strb x, [r0]
        mov r1, #0
        strb r1, [r0, #1]
        add r0, sp, #4
        add r0, #1
        str r0, [sp]
    }
    // clang-format on
    func_02015dd4(arg0, 2, call_space.bytes, &data_020d9f48);
}
