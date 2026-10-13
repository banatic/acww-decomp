/* func_ov105_0229ed78 @ 0x0229ed78, 0x20 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f54(void *p);

typedef struct {
    char pad_00[0xa0];
    int unk_A0;
} UnkStruct_0229ed78;

void func_ov105_0229ed78(UnkStruct_0229ed78 *p)
{
    func_ov002_02207e80(p, 4, 0, ~0xf);
    p->unk_A0 = func_ov002_02207f54(p);
}
