/* func_ov126_0229fe28 @ 0x0229fe28, 0x78 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_02299a00(char *p);
extern int func_ov002_0220a620(char *p, int a);
extern void func_ov095_0229c448(char *p, int a, int b);
extern void func_ov095_0229c8e4(char *p, int a);
extern void func_ov126_0229feec(void *p);

extern struct {
    char pad[2];
    unsigned short flag;
} data_021fbe40;

int func_ov126_0229fe28(void *arg)
{
    int r4;
    if (!(data_021fbe40.flag & 1)) {
        return 0;
    }
    r4 = func_ov095_02299a00((char *) arg + 0x19c);
    if (r4 == -1) {
        return 0;
    }
    if (func_ov002_0220a620((char *) arg + 0x3dc4, 6) != 0 && r4 == 263) {
        return 0;
    }
    func_ov095_0229c448((char *) arg + 0x19c, r4, 9);
    func_ov095_0229c8e4((char *) arg + 0x19c, r4);
    func_ov126_0229feec(arg);
    return 1;
}
