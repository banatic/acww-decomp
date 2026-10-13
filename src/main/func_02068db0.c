/* func_02068db0 @ 0x02068db0, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
} UnkStruct_02068db0;

extern void DC_FlushRange(unsigned int param1, unsigned int param2);
extern void GX_LoadBGPltt(unsigned int param1, unsigned int param2, unsigned int param3);
extern void GX_LoadBG2Char(unsigned int param1, unsigned int param2, unsigned int param3);
extern void GX_LoadBG2Scr(unsigned int param1, unsigned int param2, unsigned int param3);

void func_02068db0(UnkStruct_02068db0 *p)
{
    unsigned int v;
    v = p->unk_04;
    DC_FlushRange(v + 2, 0x17e);
    GX_LoadBGPltt(v + 2, 2, 0x17e);
    DC_FlushRange(p->unk_08, 0x2800);
    GX_LoadBG2Char(p->unk_08, 0, 0x2800);
    DC_FlushRange(p->unk_00, 0x800);
    GX_LoadBG2Scr(p->unk_00, 0, 0x800);
}
