/* func_ov111_0229f9d4 @ 0x0229f9d4, 0x26 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov111_0229f9fc(void *argument0);
extern void func_ov111_0229f524(int);
extern void func_ov111_0229fd08(int);
extern void func_ov111_0229f854(void *receiver);

void func_ov111_0229f9d4(int value_r0)
{
    int value_r4 = value_r0;
    if (func_ov111_0229f9fc((void *) value_r0) != 0) {
        func_ov111_0229f524(value_r4);
        func_ov111_0229fd08(value_r4);
    } else {
        func_ov111_0229f854((void *) value_r4);
    }
}
