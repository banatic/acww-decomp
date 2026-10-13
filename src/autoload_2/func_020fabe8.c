/* func_020fabe8 @ 0x020fabe8, 0x78 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern void func_020fac60(void *a, void *b);
extern void func_020fad1c(void *a, void *b);

typedef struct Flags {
    unsigned : 21;
    unsigned bit21 : 1;
    unsigned bit22 : 1;
} Flags;

typedef struct UnkStruct_020fabe8 {
    Flags *flags;
} UnkStruct_020fabe8;

typedef struct Mid {
    char pad_00[0x18];
    UnkStruct_020fabe8 *inner;
} Mid;

typedef struct UnkStruct_020fabe8_2 {
    char pad_00[0x34];
    Mid *mid;
} UnkStruct_020fabe8_2;

void func_020fabe8(void *a, void *b)
{
    Flags *fp;

    fp = ((UnkStruct_020fabe8_2 *) a)->mid->inner->flags;

    if (fp->bit21) {
        func_020fac60(a, b);
        if (fp->bit22) {
            return;
        }
        func_020fad1c(a, b);
    } else {
        if (!fp->bit22) {
            func_020fad1c(a, b);
        }
        func_020fac60(a, b);
    }
}
