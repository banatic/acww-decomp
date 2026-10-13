/* func_020ba184 @ 0x020ba184, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_020ba184;

extern int DC_FlushRange(int, int);
extern void GX_BeginLoadTex(int);
extern int GX_LoadTex(int, int, int);
extern int GX_EndLoadTex(int);

int func_020ba184(UnkStruct_020ba184 *p)
{
    GX_BeginLoadTex(DC_FlushRange(p->unk_04, p->unk_08));
    return GX_EndLoadTex(GX_LoadTex(p->unk_04, p->unk_00, p->unk_08));
}
