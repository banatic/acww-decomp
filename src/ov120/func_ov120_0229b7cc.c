/* func_ov120_0229b7cc @ 0x0229b7cc, 0x2c bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov120_0229c044(void *);
extern int func_ov002_02209f64(void *);
extern int func_ov002_02208098(void *, unsigned char);

void func_ov120_0229b7cc(void *self)
{
    if (func_ov002_02209f64((char *) self + 0x6bc) == 0) {
        func_ov002_02208098(self, *(unsigned char *) ((char *) self + 0xaa));
        func_ov120_0229c044(self);
    }
}
