/* func_ov113_0229a658 @ 0x0229a658, 0x4c bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *p, int a);
extern void func_0200277c(int a);
extern void func_0200284c(int a, int b, int c);
extern void func_ov002_022080a0(void *p, int a);
extern void func_ov113_02299d84(void *p, int a);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f60(void *p);

typedef struct {
    unsigned char pad_00[0x94];
    int unk_94;
} UnkStruct_0229a658;

void func_ov113_0229a658(UnkStruct_0229a658 *arg0)
{
    int z = 0;
    if (func_ov002_02207f3c(arg0, 1)) {
        func_0200277c(2);
        func_0200284c(2, z, z);
        func_ov002_022080a0(arg0, 5);
        func_ov113_02299d84(arg0, 8);
    } else {
        func_ov002_02207e80(arg0, 2, z, z);
        arg0->unk_94 = func_ov002_02207f60(arg0);
    }
}
