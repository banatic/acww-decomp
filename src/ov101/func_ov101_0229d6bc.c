/* func_ov101_0229d6bc @ 0x0229d6bc, 0x48 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov101_0229c42c(void *self, unsigned char a, int b);
extern int func_ov002_02207cc0(int);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);

void func_ov101_0229d6bc(void *self)
{
    if (func_ov002_02207cc0((int) (char *) self + 0x21b4)) {
        if (*(unsigned char *) ((char *) self + 0xb9)) {
            (*(unsigned char *) ((char *) self + 0xb9))--;
        } else {
            func_ov101_0229c42c(self, *(unsigned char *) ((char *) self + 0xb0), 1);
            func_ov002_02208098(self, 2);
        }
    }
}
