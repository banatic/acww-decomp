/* func_ov093_022993c0 @ 0x022993c0, 0x58 bytes, Thumb, module ov093
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov093_022990e8(char *a, int b, char *c);
extern void func_ov093_02298fa4(char *a, int b);
extern void func_0200284c(int a, int b, int c);

void func_ov093_022993c0(char *a1, int a2, int a3)
{
    int count;
    char *p;

    if (a3 < 0) {
        return;
    }
    count = (a3 >> 3) + 1;
    if (a2 == 4) {
        p = a1 + 0x820;
    } else {
        p = a1 + 0x18;
    }
    while (count > *(short *) p) {
        func_ov093_022990e8(a1, a2, p);
        func_ov093_02298fa4(p, 2);
    }
    func_0200284c(a2, 8, a3 - 0xc0);
}
