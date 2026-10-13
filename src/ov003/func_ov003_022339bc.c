/* func_ov003_022339bc @ 0x022339bc, 0x34 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_022353a4(void *a, int b, int c);

void func_ov003_022339bc(char *self)
{
    switch (*(signed char *) (self + 0x24d)) {
        case 0x1b:
        case 0x1c:
        case 0x1d:
            if (*(unsigned char *) (self + 0x254) < 5) {
                func_ov003_022353a4(self, 0, 1);
            }
    }
}
