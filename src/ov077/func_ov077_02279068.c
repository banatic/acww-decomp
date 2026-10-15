/* func_ov077_02279068 @ 0x02279068, 0x5c bytes, Thumb, module ov077
 * mwccarm 1.2/base -O4,s
 */

extern int func_020912d4(int, void *, int, int);
extern int func_0200442c(void *, int, int, int);
extern void func_02035684(int, int, int);

int func_ov077_02279068(unsigned char *self)
{
    *(unsigned int *) (self + 0x198) = 0x1000;
    *(unsigned int *) (self + 0x724) = func_020912d4(0x30, self + 0x5c, 0, 0);
    func_0200442c(self + 0x514, 0x7e6, 0x7f, 0);
    *(unsigned char *) (self + 0x510) = 1;
    func_02035684(0x17, 0xf, 0);
    return 1;
}
