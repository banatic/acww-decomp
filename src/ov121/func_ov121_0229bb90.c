/* func_ov121_0229bb90 @ 0x0229bb90, 0x40 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov121_0229a358(void *);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern void func_ov002_02208090(void *, int);
extern void func_ov002_02207e80(void *, int, int, int);
extern int func_ov002_02207f60(void *);

typedef struct UnkStruct_0229bb90 {
    char pad_00[0x94];
    int unk_94;
} UnkStruct_0229bb90;

void func_ov121_0229bb90(UnkStruct_0229bb90 *p)
{
    func_ov121_0229a358(p);
    func_ov002_02207f04(p, 8, 0, 0, 0x30);
    func_ov002_02208090(p, 3);
    func_ov002_02207e80(p, 6, 0, 0);
    p->unk_94 = func_ov002_02207f60(p);
}
