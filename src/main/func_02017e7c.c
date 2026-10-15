/* func_02017e7c @ 0x02017e7c, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern volatile unsigned short data_020c80f8;

extern int func_020164cc(void *, int);
extern int func_02095a28(void);
extern void func_02016764(void *, void *, int, int, int, int, int, int);
extern void func_02012444(int, int, int);

void func_02017e7c(void *a0, void *a1)
{
    if (func_020164cc((char *) a1 + 0x334, (int) a1)) {
        if (func_02095a28()) {
            unsigned short g = data_020c80f8;
            int f;

            func_02016764((char *) a1 + 0x334, a1, 0x23, data_020c80f8, 0, 0x1000, 0, 0);

            f = *(int *) ((char *) a1 + 0x628);
            if (f != 0) {
                func_02012444(f, g, 0);
            }

            *((unsigned char *) a0 + 0x98) = 8;
        }
    }
}
