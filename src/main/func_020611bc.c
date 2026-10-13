/* func_020611bc @ 0x020611bc, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x448];
    unsigned short unk_448;
    char pad_44A[4];
    unsigned char unk_44E;
} UnkStruct_020611bc;

void func_020611bc(UnkStruct_020611bc *base, unsigned short *src, int flag)
{
    unsigned char b;
    base->unk_448 = *src;
    b = base->unk_44E;
    b = (b & ~1) | ((unsigned char) flag & 1);
    base->unk_44E = b;
}
