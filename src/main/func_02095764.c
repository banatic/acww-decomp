/* func_02095764 @ 0x02095764, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718(int);
extern void func_020110c4(unsigned short *, int);

void func_02095764(unsigned short *out, int param)
{
    unsigned short tmp;
    int ret;

    ret = func_02096718(param);
    *out = 0xFFF1;
    if (ret) {
        func_020110c4(&tmp, ret);
        *out = tmp;
    }
}
