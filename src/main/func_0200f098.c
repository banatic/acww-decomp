/* func_0200f098 @ 0x0200f098, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200f290(void *self, int arg);
extern void func_02011404(void *ptr, int a, int b, int c, int d);
extern void func_0200f268(void *self, int arg);

void func_0200f098(void *self)
{
    if (func_0200f290(self, 0x15)) {
        func_02011404((char *) self + 0x45c, *(short *) ((char *) self + 0x460), 0x400, 0x1770000, 0xC0000);
        func_02011404((char *) self + 0x45e, *(short *) ((char *) self + 0x462), 0x400, 0x1770000, 0xC0000);
        if (*(short *) ((char *) self + 0x460) == 0 && *(short *) ((char *) self + 0x462) == 0 &&
            *(short *) ((char *) self + 0x45c) == 0 && *(short *) ((char *) self + 0x45e) == 0) {
            func_0200f268(self, 0x15);
        }
    }
}
