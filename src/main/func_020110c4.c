/* func_020110c4 @ 0x020110c4, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02011368(int a);
extern unsigned short *func_02099728(void *p);

void func_020110c4(unsigned short *out, int param)
{
    void *res;
    *out = 0xfff1;
    res = func_02011368(param);
    if (res) {
        *out = *func_02099728(res);
    }
}
