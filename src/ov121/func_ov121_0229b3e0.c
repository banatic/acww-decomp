/* func_ov121_0229b3e0 @ 0x0229b3e0, 0x2c bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f64(void *);
extern int func_ov002_02208098(void *, unsigned char);
extern void func_ov121_0229bdc0(void *);

void func_ov121_0229b3e0(void *self)
{
    if (!func_ov002_02209f64((char *) self + 0x3a8)) {
        func_ov002_02208098(self, *(unsigned char *) ((char *) self + 0xb4));
        func_ov121_0229bdc0(self);
    }
}
