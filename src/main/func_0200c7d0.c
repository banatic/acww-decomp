/* func_0200c7d0 @ 0x0200c7d0, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200c89c(void *param1, void *param2, void *param3, void *param4);
extern int func_0200c904(void *param1, unsigned short param2, unsigned char param3, unsigned char param4, int param5,
                         void *param6);

void func_0200c7d0(void *param1, void *param2)
{
    unsigned char stack[3];
    void *r5 = param1;
    void *r4 = param2;

    func_0200c89c((char *) r5 + 0x8f0, &stack[2], &stack[0], &stack[1]);
    func_0200c904(r5, *(unsigned short *) &stack[2], stack[0], stack[1], 6, r4);
}
