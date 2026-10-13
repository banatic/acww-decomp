/* func_ov108_0229da8c @ 0x0229da8c, 0x3a bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x98];
    int unk_98;
} Func_ov108Struct;

extern int func_ov002_02207f48(Func_ov108Struct *obj, int a);
extern void func_ov002_022080a0(Func_ov108Struct *obj, int a);
extern void func_ov108_0229cf4c(Func_ov108Struct *obj);
extern void func_ov002_02207e80(Func_ov108Struct *obj, int a, int b, int c);
extern int func_ov002_02207f60(Func_ov108Struct *obj);

void func_ov108_0229da8c(Func_ov108Struct *obj)
{
    if (func_ov002_02207f48(obj, 0)) {
        func_ov002_022080a0(obj, 2);
        func_ov108_0229cf4c(obj);
    }
    func_ov002_02207e80(obj, 6, 0, ~0xf);
    obj->unk_98 = func_ov002_02207f60(obj);
}
