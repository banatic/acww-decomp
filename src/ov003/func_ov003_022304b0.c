/* func_ov003_022304b0 @ 0x022304b0, 0xa4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_0223055c(void *a, int b, int c, int d, short e);
extern void func_02056fcc(void *a, int b, int c, int d, int e);

void func_ov003_022304b0(char *self)
{
    switch (*(signed char *) (self + 0x24d)) {
        case 0x1a:
            func_ov003_0223055c(self, 0xc8, 0x3c, 4, 0x38e);
            break;
        case 0x20:
            func_ov003_0223055c(self, 0x82, 0x3c, 0x10, 0x71c);
            break;
        case 0xe:
            func_ov003_0223055c(self, 0x96, 0x32, 0x18, 0x71c);
            func_02056fcc(self + 0xec, 0, 3, 0x1000, 1);
            break;
        case 0xf:
            func_ov003_0223055c(self, 0x96, 0x32, 0x18, 0x71c);
            func_02056fcc(self + 0xec, 0, 3, 0x1000, 1);
            break;
    }
}
