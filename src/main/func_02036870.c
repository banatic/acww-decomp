/* func_02036870 @ 0x02036870, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020da2f4[];

typedef struct {
    void *unk_00;
    int unk_04;
    unsigned char unk_08;
    unsigned short unk_0A;
    unsigned char unk_0C;
    unsigned char unk_0D;
    unsigned char unk_0E;
    unsigned char unk_0F;
    unsigned char unk_10;
} UnkStruct_02036870;

void func_02036870(UnkStruct_02036870 *obj, int value)
{
    obj->unk_00 = &data_020da2f4;
    obj->unk_04 = value;
    obj->unk_08 = 0x3f;
    obj->unk_0A = 0xffff;
    obj->unk_0C = 0;
    obj->unk_0D = 0;
    obj->unk_0E = 0;
    obj->unk_0F = 0;
    obj->unk_10 = 0;
}
