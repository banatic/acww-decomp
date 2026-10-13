/* func_ov003_022339f0 @ 0x022339f0, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_022353a4(void *a, int b, int c);

void func_ov003_022339f0(char *self)
{
    switch (*(signed char *) (self + 0x24d)) {
        case 0xc:
        case 0xd:
            func_ov003_022353a4(self, 0, 1);
    }
}
