/* func_ov002_0220b5ec @ 0x0220b5ec, 0x50 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208aef0(void *self);
extern int func_0208f0c0(void *self);
extern void func_0208f184(void *self, int *a, int *b);

int func_ov002_0220b5ec(void *self, int k)
{
    int v = func_0208aef0(self);

    if (func_0208f0c0(self) == 2) {
        int a;
        int b;

        func_0208f184(self, &a, &b);
        v += a;
    }
    switch (k) {
        case 0:
        case 2:
            v += 0x10;
            break;
        case 1:
        case 3:
            v += 0x20;
            break;
    }
    return v;
}
