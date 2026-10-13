/* func_ov131_0229b4cc @ 0x0229b4cc, 0x38 bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fca4(void *self);
extern void func_ov130_0229a6d8(void *ptr, unsigned char val, int a, int b);
extern void func_ov131_0229ae0c(void *self);

void func_ov131_0229b4cc(void *self)
{
    int result;
    unsigned char byte_val;

    result = func_0206fca4(self);
    byte_val = (unsigned char) (result - 0x34);
    func_ov130_0229a6d8((char *) self + 0x2c4, byte_val, 6, 4);
    func_ov131_0229ae0c(self);
    *((unsigned short *) ((char *) self + 0x1554)) = 0;
}
