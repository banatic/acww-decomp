/* func_02003064 @ 0x02003064, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void DC_FlushRange(void *, int);
extern void GX_LoadOBJPltt(void *, int, int);
extern void GXS_LoadOBJPltt(void *, int, int);

struct UnkStruct_02003064 {
    unsigned char pad_00[0x48];
    void *unk_48;
};

void func_02003064(struct UnkStruct_02003064 *p)
{
    DC_FlushRange(p->unk_48, 0x80);
    GX_LoadOBJPltt(p->unk_48, 0, 0x80);
    GXS_LoadOBJPltt(p->unk_48, 0, 0x80);
}
