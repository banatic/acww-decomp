/* func_0200f2a0 @ 0x0200f2a0, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200f290(void *self, int a);
extern void func_020044b0(void *dest, void *src, int len, int flag);

void func_0200f2a0(void *self, void *param2, void *param3)
{
    int flags;
    int f4;
    int f2;

    flags = *(int *) ((char *) self + 0xb0);
    f4 = (flags & 4) ? 1 : 0;
    if (f4 != 0) {
        f2 = (flags & 2) ? 1 : 0;
        if (f2 != 0) {
            return;
        }
    }
    if (func_0200f290(self, 25) != 0) {
        func_020044b0((char *) self + 0x83c, param2, 0x7f, 0);
    } else {
        func_020044b0((char *) self + 0x880, param2, 0x7f, 0);
    }
    *(int *) ((char *) self + 0x8c4) = ((int *) param3)[0];
    *(int *) ((char *) self + 0x8c8) = ((int *) param3)[1];
    *(int *) ((char *) self + 0x8cc) = ((int *) param3)[2];
}
