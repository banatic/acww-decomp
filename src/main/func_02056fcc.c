/* func_02056fcc @ 0x02056fcc, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned int unk_10;
    unsigned char unk_14;
} UnkStruct_02056fcc;

void func_02056fcc(UnkStruct_02056fcc *s, unsigned int param1, unsigned char param2, unsigned int param3,
                   unsigned short param4)
{
    if (param4 == 0xFFFF) {
        param4 = (unsigned short) (param1 - 1);
    }
    s->unk_04 = param1 << 12;
    s->unk_08 = param4 << 12;
    s->unk_10 = param3;
    s->unk_14 = param2;
    s->unk_0C = s->unk_08;
}
