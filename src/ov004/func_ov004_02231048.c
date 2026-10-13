/* func_ov004_02231048 @ 0x02231048, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *p);
extern void func_0203ee08(void *self, void *a);
extern void func_0203e020(void *self);
extern void func_ov004_0223121c(void *self, int k);
void func_ov004_02231048(unsigned char *self)
{
    unsigned char *a;
    if (func_02056f94(self + 0x188) != 0) {
        a = self;
        if (self != 0) {
            a = self + 0x290;
        }
        func_0203ee08(self, a);
        func_0203e020(self);
        func_ov004_0223121c(self, 6);
    }
}
