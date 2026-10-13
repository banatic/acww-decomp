/* func_ov094_02299c74 @ 0x02299c74, 0x5c bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206fdd4(void *p, int a, int b, int c, int d, int e);
extern void func_ov094_022999a8(void *p, int x);

void func_ov094_02299c74(void *arg, int idx)
{
    int a = 7;
    int b = 9;

    switch (idx) {
        case 0:
            break;
        case 1:
            b = 8;
            a = 9;
            break;
        case 2:
            b = 8;
            a = 8;
            break;
        case 3:
            b = 8;
            break;
    }

    func_0206fdd4((char *) arg + 0x1b8, a, 0xa, 0xb, 0xb, b);
    func_ov094_022999a8(arg, 1);
}
