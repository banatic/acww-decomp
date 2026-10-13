/* func_ov050_02260e50 @ 0x02260e50, 0x2e bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099fe8(void);

void func_ov050_02260e50(int *r0, int r1)
{
    int *r4 = r0;
    int r5 = r1;
    func_020984e8();
    if (r5 == 0) {
        if (func_02099fe8() >= 0) {
            r4[0x34] = 0x25;
        } else {
            r4[0x34] = 0x17;
        }
    }
}
