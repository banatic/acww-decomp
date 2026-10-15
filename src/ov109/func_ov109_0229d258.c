/* func_ov109_0229d258 @ 0x0229d258, 0x48 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207cc0(int);
extern void func_ov109_0229c418(void *self, unsigned char arg1, int arg2);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);

void func_ov109_0229d258(unsigned char *self)
{
    if (func_ov002_02207cc0((int) self + 0x218c) != 0) {
        if (self[0x29d9] != 0) {
            self[0x29d9]--;
        } else {
            func_ov109_0229c418(self, self[0x29d0], 1);
            func_ov002_02208098(self, 2);
        }
    }
}
