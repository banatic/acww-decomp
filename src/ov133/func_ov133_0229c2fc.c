/* func_ov133_0229c2fc @ 0x0229c2fc, 0x44 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *p, int x);
extern void func_ov002_022080a0(void *p, int x);
extern void func_ov133_0229bbb4(void *p);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f60(void *p);

struct Type {
    char pad_00[0x94];
    int unk_94;
};

void func_ov133_0229c2fc(struct Type *p)
{
    if (func_ov002_02207f48(p, 0)) {
        func_ov002_022080a0(p, 2);
        func_ov133_0229bbb4(p);
    }
    func_ov002_02207e80(p, 4, 0, 0);
    func_ov002_02207e80(p, 6, 0, 0);
    p->unk_94 = func_ov002_02207f60(p);
}
