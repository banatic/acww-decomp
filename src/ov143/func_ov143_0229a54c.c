/* func_ov143_0229a54c @ 0x0229a54c, 0x24 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *ptr);
extern void func_ov143_02299f84(void *self);
extern void func_ov002_02208098(void *self, unsigned char c);

void func_ov143_0229a54c(char *self)
{
    if (!func_0208e484(self + 0xac)) {
        return;
    }
    func_ov143_02299f84(self);
    func_ov002_02208098(self, *(unsigned char *) (self + 0x9e));
}
