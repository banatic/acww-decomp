/* func_02003d8c @ 0x02003d8c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern signed char data_020c7588[];

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    unsigned char unk_14;
    unsigned char unk_15;
} UnkStruct_02003d8c;

void func_02003d8c(UnkStruct_02003d8c *param0)
{
    param0->unk_00 = 3;
    param0->unk_08 = 0;
    param0->unk_04 = data_020c7588[0];
    param0->unk_0C = 0;
    param0->unk_10 = 0;
    param0->unk_14 = 0;
    param0->unk_15 = 0;
}
