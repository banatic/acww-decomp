/* func_ov119_0229b408 @ 0x0229b408, 0x48 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov119_0229ae28(void *self);
extern void func_02077c40(int x);
extern void func_ov119_0229a410(void *self, int x);
extern void func_ov119_0229a714(void *self);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
extern int func_ov119_0229ae10(void *self);

void func_ov119_0229b408(void *self)
{
    int r = func_ov119_0229ae28(self);
    if (r != 0) {
        func_02077c40(r);
        *(short *) ((char *) self + 0x9a) = -1;
        func_ov119_0229a410(self, 2);
        func_ov119_0229a714(self);
        *((char *) self + 0xb1) = 1;
        func_ov002_02208098(self, 9);
        *((char *) self + 0xb4) = (char) func_ov119_0229ae10(self);
    }
}
