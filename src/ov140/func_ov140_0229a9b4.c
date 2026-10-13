/* func_ov140_0229a9b4 @ 0x0229a9b4, 0x30 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov140_0229aedc(void *);
extern int func_ov002_02209f64(void *);
extern int func_ov002_02208098(void *, unsigned char);

void func_ov140_0229a9b4(void *self)
{
    if (func_ov002_02209f64((char *) self + 0x128c) == 0) {
        func_ov002_02208098(self, *(unsigned char *) ((char *) self + 0x8ae));
        func_ov140_0229aedc(self);
    }
}
