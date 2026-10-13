/* func_020bebec @ 0x020bebec, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    unsigned char unk_10;
    unsigned char unk_11;
} Dest;

typedef struct {
    int unk_00;
    int word1;
    int word2;
} Src;

void func_020bebec(Dest *dst, int val, Src *src, unsigned char byte)
{
    dst->unk_00 = val;
    dst->unk_04 = src->unk_00;
    dst->unk_08 = src->word1;
    dst->unk_0C = src->word2;
    dst->unk_10 = byte;
    dst->unk_11 = 1;
}
