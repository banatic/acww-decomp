/* func_ov143_02299924 @ 0x02299924, 0x80 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov143_022997d8(int, int);
extern int func_020896b8(int, void *, int, int, int, int, int);
extern void func_02088df8(int, void *, int, int, int, int, int, int, int, int, int, int);
extern void *data_ov143_0229b178[];

void func_ov143_02299924(int a0, int a1, int a2, int a3)
{
    char *p = (char *) data_ov143_0229b178[a1];
    int ret = func_ov143_022997d8(a0, a1);
    int y = a3 - (ret << 1);

    func_020896b8(1, p, a2, y, 13, 2, 0);
    func_020896b8(1, p + 8, a2, y, 13, 2, 0);
    func_02088df8(1, p + 16, a2, y, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
}
