/* func_02036034 @ 0x02036034, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02035fd8(void *p0, int p1, int p2);

void func_02036034(void *p0)
{
    int r1 = 0;
    unsigned char *r2 = *(unsigned char **) p0;
    int r3 = *(int *) (r2 + 0x1c0);
    if (r3 > 0) {
        if (*(unsigned char *) (r2 + 0x12) != 0) {
            unsigned short r4 = *(unsigned short *) (r2 + 4);
            if (r4 != 0xffff) {
                r1 = 1;
            }
        }
    }
    if (r1 != 0) {
        unsigned char *r1p = (unsigned char *) p0 + 0x74;
        unsigned char *r6 = (unsigned char *) p0 + 4;
        int r5 = 0;
        int r4 = 0;
        int r7 = 0;
        while (r1p >= r6) {
            if (*(r1p + 1) == 0) {
                int r3t = *(int *) (r1p + 0xc);
                if (*r1p != 0) {
                    r5 = 1;
                    r7 = *(int *) (r1p + 8);
                }
                if (r3t != 0) {
                    r4 = *(int *) (r1p + 4);
                }
            }
            r1p -= 0x10;
        }
        if (r5 != 0) {
            func_02035fd8((char *) r2 + 0x2b4, r4, r7);
        }
    }
}
