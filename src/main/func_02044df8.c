/* func_02044df8 @ 0x02044df8, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    unsigned char unk_04;
    unsigned char unk_05;
    unsigned char unk_06;
    int unk_08;
    int unk_0C;
    int unk_10;
    short unk_14;
} UnkStruct_02044df8;

typedef struct {
    int x;
    int y;
    int z;
} UnkStruct_02044df8_2;

void func_02044df8(UnkStruct_02044df8 *out, int f0, unsigned char f4, unsigned char f5, unsigned char f6,
                   const UnkStruct_02044df8_2 *in, short f14)
{
    out->unk_00 = f0;
    out->unk_04 = f4;
    out->unk_05 = f5;
    out->unk_06 = f6;
    out->unk_08 = in->x;
    out->unk_0C = in->y;
    out->unk_10 = in->z;
    out->unk_14 = f14;
}
