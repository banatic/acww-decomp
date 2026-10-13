/* func_ov003_0221e16c @ 0x0221e16c, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221e6a0(void *);
extern int func_02056f94(void *);
extern void func_020b2800(void *, int);
extern void func_02055124(void *);

void func_ov003_0221e16c(void *r0)
{
    void *r4 = r0;
    if (func_ov003_0221e6a0(r4) != 0) {
        if (func_02056f94((char *) r4 + 0x1d8) != 0) {
            func_020b2800(r4, 2);
            return;
        }
    }
    func_02055124((char *) r4 + 0x13c);
}
