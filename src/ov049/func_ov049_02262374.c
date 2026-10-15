/* func_ov049_02262374 @ 0x02262374, 0x40 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern int func_0201c2c8(void *a, int b);
extern int func_02019d0c(void *a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k);

int func_ov049_02262374(char *self)
{
    int r;

    r = func_0201c2c8(self, 4);
    func_02019d0c(self + 0x564, 3, 1, 0, 0, 0, r, 0, 0, data_020c80f8, 0);
    return 1;
}
