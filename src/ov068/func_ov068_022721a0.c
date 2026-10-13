/* func_ov068_022721a0 @ 0x022721a0, 0x44 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov068_02272a7c(void *self, int a);
extern void func_02095518(int a, int b, int c);
extern void func_02055124(void *p);

void func_ov068_022721a0(void *self)
{
    if (*(unsigned char *) ((char *) self + 0x2da) == 0) {
        func_ov068_02272a7c(self, 0xf);
    }
    if (*(unsigned char *) ((char *) self + 0x2da) != 0) {
        func_02095518(0, 0, 4);
        (*(unsigned char *) ((char *) self + 0x2da))--;
    }
    func_02055124((char *) self + 0x13c);
}
