/* func_020187b8 @ 0x020187b8, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int low : 12;
    unsigned int mid : 16;
    unsigned int high : 4;
} Bitfield;

extern int func_020164cc(void *p, int);
extern int func_02095a28(void);
extern void func_02016764(void *a, void *b, int c, unsigned short d, int e, int f, int g, int h);
extern void func_02012444(unsigned int target, unsigned short val, int flag);
extern int func_0200442c(void *ptr, int v1, int v2, int v3);
extern volatile unsigned short data_020c80f8;

void func_020187b8(char *param0, char *param1)
{
    if (func_020164cc(param1 + 0x334, (int) param1) != 0) {
        if (func_02095a28() != 0) {
            unsigned short v = data_020c80f8;
            func_02016764(param1 + 0x334, param1, 0x23, data_020c80f8, 0, 0x1000, 0, 0);
            if (*(unsigned int *) (param1 + 0x628) != 0) {
                func_02012444(*(unsigned int *) (param1 + 0x628), v, 0);
            }
            *(unsigned char *) (param0 + 0x98) = 1;
        }
    } else {
        if (((Bitfield *) (param1 + 0x190))->mid == 8) {
            func_0200442c(param1 + 0x514, 0x63, 0x7f, 0);
        }
    }
}
