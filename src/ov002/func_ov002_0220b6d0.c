/* func_ov002_0220b6d0 @ 0x0220b6d0, 0x24 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_02068320(void *p);

int func_ov002_0220b6d0(char *self)
{
    int *p = *(int **) (self + 0x110);

    if (p[1] == 0) {
        func_02068320(p);
        return 1;
    }
    return 0;
}
