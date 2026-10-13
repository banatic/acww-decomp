/* func_0203f728 @ 0x0203f728, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned short unk_0C;
    unsigned int unk_10;
    unsigned int unk_14;
} UnkStruct_0203f728;

extern int FX_Div(int a, int b);

UnkStruct_0203f728 *func_0203f728(UnkStruct_0203f728 *p)
{
    p->unk_00 = 0;
    p->unk_04 = 0;
    p->unk_08 = 0;
    p->unk_0C = 0;
    p->unk_14 = FX_Div(0x1000, 0xA000);
    p->unk_10 = 0xE000;
    return p;
}
