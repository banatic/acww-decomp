/* func_ov096_0229fe9c @ 0x0229fe9c, 0x30 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229e2c8(void *self, unsigned char byte);
extern void func_ov096_0229e6a0(void *self);
extern void func_ov094_02299d34(void *ptr);
extern int func_ov096_0229fb9c(void *self);

int func_ov096_0229fe9c(void *self)
{
    int ret = func_ov096_0229e2c8(self, *(unsigned char *) ((char *) self + 0xc0));
    if (ret != 0) {
        return ret;
    }
    func_ov096_0229e6a0(self);
    func_ov094_02299d34((char *) self + 0xde0);
    return func_ov096_0229fb9c(self);
}
