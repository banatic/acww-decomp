/* func_02017d14 @ 0x02017d14, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern volatile unsigned short data_020c80f8;

extern int func_020164cc(void *p);
extern int func_02016764(void *a, void *b, int c, unsigned short d, int e, int f, int g, int h);
extern void func_02012444(unsigned int a, unsigned short b, int c);
extern void func_02057cb8(void *p);
extern void func_02019af0(void *p, int n);

void func_02017d14(void *p0, void *p1)
{
    if (func_020164cc((char *) p1 + 0x334)) {
        unsigned short saved = data_020c80f8;
        func_02016764((char *) p1 + 0x334, p1, 0, data_020c80f8, 0, 0x1000, 0, 0);
        if (*(unsigned int *) ((char *) p1 + 0x628) != 0) {
            func_02012444(*(unsigned int *) ((char *) p1 + 0x628), saved, 0);
        }
        func_02057cb8(p1);
        func_02019af0(p0, 1);
        *(unsigned char *) ((char *) p0 + 0x98) = 0x14;
    }
}
