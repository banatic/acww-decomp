/* func_ov095_0229a280 @ 0x0229a280, 0x58 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov095_022999a8(void *self, int arg);

void func_ov095_0229a280(void *self)
{
    unsigned char c = ((unsigned char *) self)[0x42];

    switch (c) {
        case 0:
            if (*(unsigned int *) ((char *) self + 0x28) == 0x10a) {
                *(unsigned int *) ((char *) self + 0x28) = 0xf7;
            } else {
                func_ov095_022999a8(self, 0x10);
            }
            break;

        case 1:
        case 2:
            *(unsigned int *) ((char *) self + 0x28) = 0x103;
            break;

        case 3:
        case 4:
        case 5:
            func_ov095_022999a8(self, 0x10);
            break;
    }
}
