/* func_ov103_0229d21c @ 0x0229d21c, 0x54 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f9c(unsigned char *p);
extern unsigned char *func_ov002_02208098(unsigned char *self, unsigned char value);
extern int func_ov103_0229cd4c(unsigned char *self, int arg1);
extern void func_ov103_0229ca48(unsigned char *self);
extern void func_ov103_0229c994(unsigned char *self);
extern void func_ov103_0229ce18(unsigned char *self, int a, int b);

void func_ov103_0229d21c(unsigned char *self)
{
    if (func_ov002_02209f9c(self + 0x2274) == 0) {
        unsigned char b = self[0x2da6];
        unsigned char a = self[0x2da4];
        if (a == b) {
            func_ov103_0229cd4c(self, b);
            func_ov103_0229ca48(self);
            func_ov002_02208098(self, 5);
        } else {
            func_ov103_0229ce18(self, b, 4);
        }
    } else {
        func_ov103_0229c994(self);
    }
}
