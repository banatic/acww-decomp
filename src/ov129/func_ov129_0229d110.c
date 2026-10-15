/* func_ov129_0229d110 @ 0x0229d110, 0x70 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b177c(void *ptr, int a);
extern void func_ov127_0229a04c(void *ptr, int a);
extern void func_ov127_02299fd4(unsigned char *self, unsigned char val, int mode);
extern void func_ov127_02299f90(void *receiver);
extern void func_ov002_0220af94(void *receiver);
extern int func_ov002_0220abbc(void *ptr);
extern void func_ov002_0220a63c(void *ptr, int a);
extern void func_ov002_0220a658(void *ptr, int a);

void func_ov129_0229d110(void *self)
{
    func_ov127_0229a04c((char *) self + 0x734, 3);
    func_ov127_02299fd4((unsigned char *) self + 0x734, 6, 1);
    func_020b177c((char *) self + 0x404, 3);
    func_ov127_02299f90((void *) ((char *) self + 0x734));
    func_ov002_0220af94((void *) ((char *) self + 0x1d4));
    func_ov002_0220abbc((char *) self + 0x1d4);
    if (*(unsigned char *) ((char *) self + 0xb1) == 2) {
        func_ov002_0220a63c((char *) self + 0x1d4, 6);
    } else {
        func_ov002_0220a658((char *) self + 0x1d4, 6);
    }
}
