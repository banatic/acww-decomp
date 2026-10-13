/* func_ov051_022611e0 @ 0x022611e0, 0x3c bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021c75b8;
extern int func_020e8840(void *ptr);
extern void func_ov051_0226122c(char *self, int arg);

int func_ov051_022611e0(char *self)
{
    unsigned int flag = (data_021c75b8 == 2) ? 1 : 0;
    if (flag > 0) {
        if (func_020e8840(self + 0x718) == 0) {
            func_ov051_0226122c(self, 1);
        }
    }
    return 1;
}
