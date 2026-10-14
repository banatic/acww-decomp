/* func_ov068_022759d0 @ 0x022759d0, 0x28 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
} Pair;

typedef struct {
    char pad_00[0x510];
    char flag;
    char pad_511[0x533];
    Pair pair;
} Dest;

extern Pair __ptmf_null;

int func_ov068_022759d0(Dest *dst)
{
    dst->pair = __ptmf_null;
    dst->flag = 1;
    return 1;
}
