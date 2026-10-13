/* func_020ad8f8 @ 0x020ad8f8, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_ov004_022460c8(int a, int b, int c);
extern int func_020ae8cc(void *p, unsigned short *q);
extern void func_020b0200(void *p);
extern void func_020adb70(int a, int b, int c, int d, int e, int f, int g);
extern int data_021f3b44;
extern int data_021f49ec;

void func_020ad8f8(int a, int b, int c)
{
    unsigned short tmp;
    int res;
    tmp = *func_ov004_022460c8(a, b, c);
    res = func_020ae8cc((void *) &data_021f3b44, &tmp);
    if (res != -1) {
        func_020b0200((void *) &data_021f49ec);
        func_020adb70(res, 0, c, 1, 1, 1, 0);
    }
}
