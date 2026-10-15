/* func_ov102_0229e410 @ 0x0229e410, 0x48 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229e410 {
    char pad_00[0x24d0];
    int unk_24D0;
} UnkStruct_0229e410;

extern int func_ov002_02207f48(UnkStruct_0229e410 *p, int x);
extern void func_ov002_02207e80(void *, int, int, int);
extern int func_ov002_02207f60(UnkStruct_0229e410 *p);
extern void func_ov102_0229dff0(UnkStruct_0229e410 *p);
extern void func_ov102_0229e4f4(UnkStruct_0229e410 *p);
extern void func_ov002_02208090(UnkStruct_0229e410 *p, int x);

void func_ov102_0229e410(UnkStruct_0229e410 *p)
{
    int ret = func_ov002_02207f48(p, 0);
    func_ov002_02207e80(p, 6, 0LL, 0);
    p->unk_24D0 = func_ov002_02207f60(p);
    if (ret != 0) {
        func_ov102_0229dff0(p);
        func_ov102_0229e4f4(p);
        func_ov002_02208090(p, 3);
    }
}
