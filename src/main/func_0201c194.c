/* func_0201c194 @ 0x0201c194, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201ae40(void *a);
extern int func_0201c208(void *a, void *b, void *tab);

extern int data_021c16c0;
extern int data_021c16b4;

int func_0201c194(char *self, int *out)
{
    int ret;
    int *src;
    int m;

    m = func_0201ae40(self + 0x3a8);
    ret = 0;
    src = (int *) (self + 0x5c);
    out[0] = src[0];
    out[1] = src[1];
    out[2] = src[2];
    switch (m) {
        case 3:
            ret = 1;
            break;
        case 1:
            if (func_0201c208(self, out, &data_021c16c0)) {
                ret = 2;
            } else {
                ret = 1;
            }
            break;
        case 2:
            if (func_0201c208(self, out, &data_021c16b4)) {
                ret = 2;
            } else {
                ret = 1;
            }
            break;
    }
    return ret;
}
