/* func_02014788 @ 0x02014788, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    unsigned short unk_04;
    unsigned short unk_06;
    unsigned char unk_08;
    unsigned char unk_09;
    unsigned char unk_0A;
    unsigned char unk_0B;
    unsigned char unk_0C;
    unsigned char unk_0D;
} UnkStruct_02014788;

int func_02014788(UnkStruct_02014788 *obj, unsigned char param2, int param3, unsigned short param4, short param5,
                  unsigned char param6, unsigned char param7)
{
    int ret = 0;
    if (obj->unk_09 == 5) {
        obj->unk_09 = param2;
        obj->unk_04 = param4;
        obj->unk_06 = param5;
        obj->unk_00 = param3;
        obj->unk_0D = param6;
        obj->unk_0C = param7;
        ret = 1;
    }
    return ret;
}
