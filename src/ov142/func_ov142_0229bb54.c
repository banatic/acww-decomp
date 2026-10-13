/* func_ov142_0229bb54 @ 0x0229bb54, 0x2e bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x98];
    int unk_98;
} UnkStruct_0229bb54;

extern int func_ov002_02207f48(UnkStruct_0229bb54 *p, int a);
extern void func_ov142_0229b214(UnkStruct_0229bb54 *p);
extern void func_ov002_022080a0(UnkStruct_0229bb54 *p, int b);
extern int func_ov002_02207f60(UnkStruct_0229bb54 *p);

void func_ov142_0229bb54(UnkStruct_0229bb54 *p)
{
    if (func_ov002_02207f48(p, -1)) {
        func_ov142_0229b214(p);
        func_ov002_022080a0(p, 2);
    }
    p->unk_98 = func_ov002_02207f60(p);
}
