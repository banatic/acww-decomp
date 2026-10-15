/* func_ov068_02266df4 @ 0x02266df4, 0x84 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov068_0226d598(int);
extern int func_020984e8(void);
extern int func_0201c330(int, int, int);
extern int func_02081edc(void *record);
extern int func_02014868(int);
extern int func_ov068_0226cc00(int);
extern int func_0201ce18(int);
extern int func_0201cddc(int);
int func_ov068_02266df4(int receiver)
{
    int record;
    record = func_ov068_0226d598(receiver);
    if (func_020984e8() != 0) {
        record = func_ov068_0226d598(receiver);
    }
    if (record == 0) {
        if (func_0201c330(receiver, 0x6000, 4) == 0) {
            goto label_02266e30;
        }
    }
    if (record != 0) {
        if (func_02081edc((void *) record) != 0) {
        label_02266e30:
            if (func_02014868(receiver + 0x618) == 0) {
                if (func_ov068_0226cc00(receiver + 0x8b8) != 0) {
                    if (func_0201ce18(receiver) == 0) {
                        if (func_0201cddc(receiver) == 0xb) {
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
