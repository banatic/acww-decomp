/* func_0200faa8 @ 0x0200faa8, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02011404(short *p, int a, int b, int c, int d);
extern void func_020110a0(char *p, short *s);

int func_0200faa8(char *param0, int param1)
{
    short s;
    int ret;

    s = *(short *) (param0 + 0x8e);
    if (func_02011404(&s, -32768, param1, 0x01770000, 0x000c0000) == 0) {
        ret = 1;
    } else {
        ret = 0;
    }
    func_020110a0(param0, &s);
    return ret;
}
