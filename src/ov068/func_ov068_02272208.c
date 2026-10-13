/* func_ov068_02272208 @ 0x02272208, 0x30 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *);
extern void func_ov068_02272a7c(void *, int);
extern void func_02055124(void *);

void func_ov068_02272208(void *this)
{
    if (func_02056f94((char *) this + 0x1d8)) {
        func_ov068_02272a7c(this, 0xe);
    }
    func_02055124((char *) this + 0x13c);
}
