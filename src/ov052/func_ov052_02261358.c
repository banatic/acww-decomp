/* func_ov052_02261358 @ 0x02261358, 0x40 bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern int func_02019d0c(unsigned char *, int, int, int, int, int, int, int, int, int, int);

int func_ov052_02261358(unsigned char *self)
{
    self[0x731] = 50;
    func_02019d0c(self + 0x564, 1, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
