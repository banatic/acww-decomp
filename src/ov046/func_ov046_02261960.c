/* func_ov046_02261960 @ 0x02261960, 0x6c bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern unsigned int data_020c814c;
extern int data_021fbee8;

extern void func_02019d0c(unsigned char *a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k);
extern void func_0201ad18(unsigned char *a, int b, int c, int d, void *e, int f, int g, int h);

int func_ov046_02261960(unsigned char *self)
{
    func_02019d0c(self + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    *(unsigned short *) (self + 0x738) = 0x78;
    func_0201ad18(self + 0x3b0, 1, 0, 0, &data_021fbee8, 4, data_020c814c, 1);
    return 1;
}
