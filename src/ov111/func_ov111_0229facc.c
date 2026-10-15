/* func_ov111_0229facc @ 0x0229facc, 0x26 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov111_0229faf4(void *);
extern void func_ov111_0229f524(void *);
extern void func_ov111_0229fd08(void *);
extern void func_ov111_0229f854(void *receiver);

void func_ov111_0229facc(void *value_r0)
{
    void *value_r4 = value_r0;
    if (func_ov111_0229faf4(value_r4) != 0) {
        func_ov111_0229f524(value_r4);
        func_ov111_0229fd08(value_r4);
    } else {
        func_ov111_0229f854((void *) value_r4);
    }
}
