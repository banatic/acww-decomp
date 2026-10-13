/* func_020605d8 @ 0x020605d8, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b9ec4(void *p);
extern void func_020ba004(void *p);

void func_020605d8(unsigned char *self, int idx)
{
    unsigned int flag;
    unsigned char *p;
    int o;

    o = idx * 28;
    p = self + o + 0xe5;
    flag = (*p == 1);
    if (flag > 0) {
        func_020b9ec4(self + 0xd8 + o);
    } else {
        func_020ba004(self + 0xd8 + o);
    }
}
