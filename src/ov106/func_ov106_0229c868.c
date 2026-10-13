/* func_ov106_0229c868 @ 0x0229c868, 0x2c bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov106_0229ca5c(void *p);
extern void func_ov002_022096d8(void *p, int v);
extern void func_ov002_02208098(void *p, int v);

void func_ov106_0229c868(void *self)
{
    unsigned char *p = (unsigned char *) self + 0xbc;
    *p = 4;
    func_ov106_0229ca5c(self);
    func_ov002_022096d8((char *) self + 0x2304, 0);
    func_ov002_02208098(self, 0x18);
}
