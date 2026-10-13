/* func_ov099_0229dae8 @ 0x0229dae8, 0x3c bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

typedef struct StructName {
    char pad_00[0x27ec];
    int unk_27EC;
} StructName;

extern int func_ov002_02207f48(StructName *p, int a);
extern void func_ov002_022080a0(StructName *p, int a);
extern void func_ov002_02207e80(StructName *p, int a, int b, int c);
extern int func_ov002_02207f60(StructName *p);
extern void func_ov099_0229d0f0(StructName *p);

void func_ov099_0229dae8(StructName *p)
{
    if (func_ov002_02207f48(p, 0)) {
        func_ov002_022080a0(p, 2);
        func_ov099_0229d0f0(p);
    }
    func_ov002_02207e80(p, 6, 0, 0);
    p->unk_27EC = func_ov002_02207f60(p);
}
