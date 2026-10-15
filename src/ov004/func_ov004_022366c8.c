/* func_ov004_022366c8 @ 0x022366c8, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern const unsigned char data_ov004_02247924[];
extern void func_ov004_022354e0(void *self);
extern void func_02055dc8(void *p, void *fn, void *self);
extern void func_ov004_0223653c(char *arg0);

void func_ov004_022366c8(void *self)
{
    if (data_ov004_02247924[*(int *) ((char *) self + 0x15c) * 0x11] == 0) {
        *(void **) ((char *) self + 0x50) = self;
    }
    *((char *) self + 0x1e8) = (char) *(int *) ((char *) self + 0x15c);
    func_ov004_022354e0(self);
    if (*((unsigned char *) self + 0x1c6) != 0) {
        func_02055dc8((char *) self + 0x64, (void *) func_ov004_0223653c, self);
    }
}
