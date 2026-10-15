/* func_ov099_0229d400 @ 0x0229d400, 0x4c bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f64(void *p);
extern unsigned char *func_ov002_02208098(void *p, unsigned char c);
extern void func_ov099_0229cb8c(void *p, unsigned char c);
extern void func_ov099_0229c928(void *p);

void func_ov099_0229d400(unsigned char *self)
{
    if (!func_ov002_02209f64(self + 0x2274)) {
        func_ov002_02208098(self, self[0x290a]);
        if ((unsigned char) (self[0x290a] + 0xFC) <= 1) {
            func_ov099_0229cb8c(self, self[0x2907]);
        }
    }
    func_ov099_0229c928(self);
}
