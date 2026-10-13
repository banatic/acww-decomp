/* func_0205007c @ 0x0205007c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x150];
    unsigned int unk_150;
    unsigned int unk_154;
    unsigned int unk_158;
} Dest;

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
} Src;

void func_0205007c(Dest *dst, Src *src)
{
    dst->unk_150 = src->unk_00;
    dst->unk_154 = src->unk_04;
    dst->unk_158 = src->unk_08;
}
