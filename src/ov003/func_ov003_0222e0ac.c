/* func_ov003_0222e0ac @ 0x0222e0ac, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0222ea04(void *a, void *b, int c);
extern char data_ov003_022617bc[];
extern char data_ov003_02260994[];
extern char data_ov003_02260e4c[];

int func_ov003_0222e0ac(void *self)
{
    int r = func_ov003_0222ea04(self, data_ov003_022617bc, 8);
    r &= func_ov003_0222ea04(self, data_ov003_02260994, 2);
    r &= func_ov003_0222ea04(self, data_ov003_02260e4c, 4);
    return r;
}
