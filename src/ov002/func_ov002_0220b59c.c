/* func_ov002_0220b59c @ 0x0220b59c, 0x50 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208aeec(void *self);
extern int func_0208f0c0(void *self);
extern void func_0208f184(void *self, int *a, int *b);

int func_ov002_0220b59c(void *self, int k)
{
    int v = func_0208aeec(self);

    if (func_0208f0c0(self) == 2) {
        int a;
        int b;

        func_0208f184(self, &a, &b);
        v += b;
    }
    switch (k) {
        case 0:
        case 1:
            v += 8;
            break;
        case 2:
            break;
        case 3:
            v += 8;
            break;
    }
    return v;
}
