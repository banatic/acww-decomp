/* func_ov068_0226da28 @ 0x0226da28, 0x3c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207f270(void *p);
extern int func_02079544(int v);

typedef struct {
    char pad_00[0x830];
    void *unk_830;
} UnkStruct_0226da28;

int func_ov068_0226da28(UnkStruct_0226da28 *p)
{
    int r6 = 0;
    int r4 = r6;
    if (p->unk_830 != 0 && func_0207f270(p->unk_830) != 0) {
        r4 = 1;
    }
    if (r4 != 0 && func_02079544(func_0207f270(p->unk_830)) == 1) {
        r6 = 1;
    }
    return r6;
}
