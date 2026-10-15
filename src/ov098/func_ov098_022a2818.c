/* func_ov098_022a2818 @ 0x022a2818, 0x6c bytes, Thumb, module ov098
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220b74c(char *p);
extern int func_0206f56c(void);
extern unsigned char *func_ov002_02208098(char *p, unsigned char value);
extern int func_ov002_0220b740(char *p);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern unsigned short data_021fbe40[];

void func_ov098_022a2818(char *self)
{
    unsigned int b;
    func_ov002_0220b74c(self + 0x2958);
    if (func_0206f56c() != 0) {
        goto call;
    }
    b = (data_021fbdd8 && data_021fbddc);
    if (b != 0) {
        goto call;
    }
    if (data_021fbe40[1] & 1) {
        goto call;
    }
    if (data_021fbe40[1] & 2) {
        goto call;
    }
    return;
call:
    func_ov002_02208098(self, 0x38);
    func_ov002_0220b740(self + 0x2958);
}
