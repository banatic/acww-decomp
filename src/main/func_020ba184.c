/* func_020ba184 @ 0x020ba184, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
    void *unk_04;
    unsigned int unk_08;
} UnkStruct_020ba184;

extern void DC_FlushRange(void *, unsigned int);
extern void GX_BeginLoadTex(void);
extern void GX_LoadTex(const void *, unsigned int, unsigned int);
extern void GX_EndLoadTex(void);

void func_020ba184(UnkStruct_020ba184 *p)
{
    DC_FlushRange(p->unk_04, p->unk_08);
    GX_BeginLoadTex();
    GX_LoadTex(p->unk_04, p->unk_00, p->unk_08);
    GX_EndLoadTex();
}
