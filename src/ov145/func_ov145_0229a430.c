/* func_ov145_0229a430 @ 0x0229a430, 0x26 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov145_0229aa64(void *);
extern int func_ov002_02209f64(void *);
extern int func_ov002_02208098(void *, unsigned char);

void func_ov145_0229a430(void *self)
{
    if (func_ov002_02209f64((char *) self + 0xc8) == 0) {
        func_ov002_02208098(self, *(unsigned char *) ((char *) self + 0xc3));
        func_ov145_0229aa64(self);
    }
}
