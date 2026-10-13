/* func_ov108_0229d9e0 @ 0x0229d9e0, 0x4c bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229d9e0 {
    char pad_00[0x98];
    int unk_98;
} UnkStruct_0229d9e0;

extern int func_ov002_02207f3c(UnkStruct_0229d9e0 *p, int arg);
extern void func_020027f0(int arg);
extern void func_ov108_0229c2bc(UnkStruct_0229d9e0 *p, int arg);
extern void func_ov002_022080a0(UnkStruct_0229d9e0 *p, int arg);
extern void func_ov002_02207e80(UnkStruct_0229d9e0 *p, int a, int b, int c);
extern int func_ov002_02207f60(UnkStruct_0229d9e0 *p);

void func_ov108_0229d9e0(UnkStruct_0229d9e0 *p)
{
    if (func_ov002_02207f3c(p, 0) != 0) {
        func_020027f0(6);
        func_ov108_0229c2bc(p, 2);
        func_ov108_0229c2bc(p, 1);
        func_ov002_022080a0(p, 5);
    } else {
        func_ov002_02207e80(p, 6, 0, -16);
    }
    p->unk_98 = func_ov002_02207f60(p);
}
