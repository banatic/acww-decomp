/* func_ov111_0229facc @ 0x0229facc, 0x26 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov111_0229faf4(void *);
extern int func_ov111_0229f524(void *);
extern int func_ov111_0229fd08(void *);
extern int func_ov111_0229f854(void *);

void func_ov111_0229facc(void *r0)
{
    void *r4 = r0;
    if (func_ov111_0229faf4(r4) != 0) {
        func_ov111_0229f524(r4);
        func_ov111_0229fd08(r4);
    } else {
        func_ov111_0229f854(r4);
    }
}
