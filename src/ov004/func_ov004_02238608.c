/* func_ov004_02238608 @ 0x02238608, 0x90 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f28(void *p, int k);
extern void func_020042a0(void *p, int k);

void func_ov004_02238608(void *self)
{
    unsigned char *c;

    if (func_02056f28((char *) self + 0x100, 1) != 0) {
        func_020042a0((char *) self + 0x1fc, 0x832);
        c = (unsigned char *) ((char *) self + 0x210);
        *c = (unsigned char) (*c + 1);
    }
    if (*((unsigned char *) self + 0x210) >= *((unsigned char *) self + 0x20a)) {
        if (func_02056f28((char *) self + 0x100,
                          (unsigned short) (((((unsigned int) *(int *) ((char *) self + 0x104)) << 4) >> 16) - 1)) != 0) {
            *((char *) self + 0x211) = 6;
            *(int *) ((char *) self + 0x158) = 0;
            *(int *) ((char *) self + 0x108) = 0;
            *(int *) ((char *) self + 0x110) = 0;
        }
    }
}
