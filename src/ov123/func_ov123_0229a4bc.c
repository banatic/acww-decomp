/* func_ov123_0229a4bc @ 0x0229a4bc, 0x7c bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov123_0229ae24(void *);
extern void func_ov123_02299f08(void *);
extern void func_ov123_02299878(void *);
extern void func_ov123_02299e28(void *);
extern void func_ov123_0229a538(void *, unsigned char, unsigned char);
extern void func_0200467c(int);
extern void func_ov123_02299640(void *, int);

void func_ov123_0229a4bc(void *self)
{
    unsigned char v;
    func_ov123_0229ae24(self);
    v = *(unsigned char *) ((char *) self + 0xa4);
    if (v >= 6 && v <= 8) {
        func_ov123_02299f08(self);
        func_ov123_02299878(self);
        return;
    }
    func_ov123_02299e28(self);
    func_ov123_0229a538(self, *(unsigned char *) ((char *) self + 0xa8), *(unsigned char *) ((char *) self + 0xa9));
    v = *(unsigned char *) ((char *) self + 0xa4);
    if (v <= 2) {
        func_0200467c(0x85f);
        func_0200467c(0x861);
        func_ov123_02299640(self, 0x1000);
    }
    func_ov123_02299878(self);
    func_ov123_02299640(self, 0x40);
}
