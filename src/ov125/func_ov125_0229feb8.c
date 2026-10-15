/* func_ov125_0229feb8 @ 0x0229feb8, 0x2c bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov125_0229fb7c(void *);
extern void func_ov002_02207fc0(void *);
extern void func_ov125_0229fd04(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);

void func_ov125_0229feb8(void *self)
{
    ((unsigned char *) self)[0x87a] = 9;
    func_ov125_0229fb7c(self);
    func_ov002_02207fc0(self);
    func_ov125_0229fd04(self);
    func_ov002_02208098(self, 2);
}
