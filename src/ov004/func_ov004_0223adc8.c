/* func_ov004_0223adc8 @ 0x0223adc8, 0x2a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020576cc();

void *func_ov004_0223adc8(char *self)
{
    func_020576cc(self + 0x10);
    *(int *) (self + 0xa0) = -1;
    *(short *) (self + 0xa4) = -1;
    *(int *) (self) = 0;
    *(short *) (self + 0xa6) = 0;
    return self;
}
