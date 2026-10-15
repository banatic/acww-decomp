/* func_ov096_022a05fc @ 0x022a05fc, 0x30 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov096_0229f970(void *a, unsigned char b);
extern int func_ov002_02209f9c(void *a);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov096_022a05fc(void *self)
{
    if (func_ov002_02209f9c((char *) self + 0x2500)) {
        func_ov096_0229f970(self, *(unsigned char *) ((char *) self + 0xb5));
        func_ov002_02208098((void *) (self), 0x13);
    }
}
