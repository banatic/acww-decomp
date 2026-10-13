/* func_ov112_022a0f88 @ 0x022a0f88, 0x3c bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern void func_ov112_0229f784(char *);
extern void func_ov002_0220a568(char *);
extern void func_ov112_0229ff38(char *);
extern void func_ov112_0229f9bc(char *);

void func_ov112_022a0f88(char *p)
{
    p[0xbc] = 0;
    if (data_021fbdd8 == 0) {
        func_ov112_0229f784(p);
        func_ov002_0220a568(p + 0x4234);
        func_ov112_0229ff38(p);
    } else {
        func_ov112_0229f9bc(p);
    }
}
