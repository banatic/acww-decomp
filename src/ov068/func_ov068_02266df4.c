/* func_ov068_02266df4 @ 0x02266df4, 0x84 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov068_0226d598(int);
extern int func_020984e8(void);
extern int func_0201c330(int, int, int);
extern int func_02081edc(int);
extern int func_02014868(int);
extern int func_ov068_0226cc00(int);
extern int func_0201ce18(int);
extern int func_0201cddc(int);
int func_ov068_02266df4(int r4)
{
    int r5;
    r5 = func_ov068_0226d598(r4);
    if (func_020984e8() != 0) {
        r5 = func_ov068_0226d598(r4);
    }
    if (r5 == 0) {
        if (func_0201c330(r4, 0x6000, 4) == 0) {
            goto label_02266e30;
        }
    }
    if (r5 != 0) {
        if (func_02081edc(r5) != 0) {
        label_02266e30:
            if (func_02014868(r4 + 0x618) == 0) {
                if (func_ov068_0226cc00(r4 + 0x8b8) != 0) {
                    if (func_0201ce18(r4) == 0) {
                        if (func_0201cddc(r4) == 0xb) {
                            return 1;
                        }
                    }
                }
            }

            goto label_02266e60;
        }
    }
label_02266e60:
    return 0;
}
