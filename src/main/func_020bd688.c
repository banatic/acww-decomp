/* func_020bd688 @ 0x020bd688, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020bdc50(void *self, int a, int b, int c, int d);
extern void func_020bdc14(void *self, int a);

void func_020bd688(void *self)
{
    unsigned char b = *(unsigned char *) ((char *) self + 0x2f19);
    int w = *(int *) ((char *) self + 0x0e0c);
    int flag = (w == 4);
    if (b >= 19 || b < 4) {
        if (flag) {
            return;
        }
        func_020bdc50(self, 4, 0x1f, 0, 0);
    } else {
        if (!flag) {
            return;
        }
        func_020bdc14(self, 4);
    }
}
