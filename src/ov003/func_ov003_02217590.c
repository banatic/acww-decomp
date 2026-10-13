/* func_ov003_02217590 @ 0x02217590, 0x78 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f28(void *ptr, int arg);
extern void func_0200f268(void *ptr, int arg);
extern void func_0200f27c(void *ptr, int arg);
extern void func_0200f328(void *ptr, int arg);
extern void func_02010f5c(void *ptr);

void func_ov003_02217590(unsigned char *self)
{
    func_02010f5c(self);
    if ((self[0x7e2] & 3) != 2) {
        unsigned int field = *(unsigned int *) (self + 0x2d8);
        if (((field << 4) >> 16) < 6) {
            if (func_02056f28(self + 0x2d0, 5) != 0) {
                func_0200f268(self, 0);
            }
        }
    } else {
        unsigned int field = *(unsigned int *) (self + 0x2d8);
        if (((field << 4) >> 16) < 8) {
            if (func_02056f28(self + 0x2d0, 7) != 0) {
                func_0200f27c(self, 0);
                func_0200f328(self, 0x857);
            }
        }
    }
}
