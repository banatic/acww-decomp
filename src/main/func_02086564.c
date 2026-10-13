/* func_02086564 @ 0x02086564, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644b4(int);
extern int func_0204c380(unsigned short *);
extern int func_0204c308(unsigned short *);
extern int FX_MulFunc(int, int);

int func_02086564(unsigned short *ptr)
{
    int result = 0;
    int base = func_020644b4(0x666) + 0xccd;
    int inFirst = 0;
    unsigned short val = *ptr;

    if (val >= 0x12e8 && val <= 0x131f) {
        inFirst = 1;
    }

    if (inFirst) {
        result = FX_MulFunc((func_0204c380(ptr) << 12), base);
    } else if (val >= 0x12b0 && val <= 0x12e7) {
        result = FX_MulFunc((func_0204c308(ptr) << 12), base);
    }

    return result;
}
