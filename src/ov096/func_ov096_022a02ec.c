/* func_ov096_022a02ec @ 0x022a02ec, 0x50 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *a);
extern void func_ov002_022090b0(void *a, unsigned char b);
extern unsigned char func_ov002_02208a8c(void *a, unsigned char b, unsigned char c);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov096_022a02ec(char *self)
{
    if (func_0208e484(self + 0x2500)) {
        func_ov002_022090b0(self + 0x2564, *(unsigned char *) (self + 0xbc));
        *(unsigned char *) (self + 0xbe) =
            func_ov002_02208a8c(self + 0x2564, *(unsigned char *) (self + 0xbd), *(unsigned char *) (self + 0xbc));
        func_ov002_02208098((void *) (self), 0x23);
    }
}
