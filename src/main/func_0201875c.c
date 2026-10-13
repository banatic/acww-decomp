/* func_0201875c @ 0x0201875c, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern volatile unsigned short data_020c80f8;
extern int func_02057d34(void *);
extern void func_02016764(void *, void *, int, int, int, int, int, int);
extern void func_02012444(int, int, int);

void func_0201875c(unsigned char *param0, unsigned char *param1)
{
    unsigned short v;
    int field;

    if (func_02057d34(param1) != 0) {
        return;
    }

    v = data_020c80f8;

    func_02016764(param1 + 0x334, param1, 0, data_020c80f8, 0, 0x1000, 0, 0);

    field = *(int *) (param1 + 0x628);
    if (field != 0) {
        func_02012444(field, v, 0);
    }

    param0[0x98] = 2;
}
