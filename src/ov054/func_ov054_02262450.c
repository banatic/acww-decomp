/* func_ov054_02262450 @ 0x02262450, 0x2c bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

extern int func_02095ab0(void *dst, int size, int count);
extern unsigned int data_ov054_022629c8[3];

int func_ov054_02262450(void)
{
    unsigned int local[3];
    int i;

    local[0] = data_ov054_022629c8[0];
    local[1] = data_ov054_022629c8[1];
    local[2] = data_ov054_022629c8[2];
    func_02095ab0(local, 0x400, 4);
    return 1;
}
