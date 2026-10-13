/* func_ov122_022a1bd4 @ 0x022a1bd4, 0x4e bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x8c];
    unsigned char unk_8C;
    unsigned char pad_8D[7];
    int unk_94;
    unsigned char pad_98[29];
    unsigned char unk_B5;
} Object;

extern int func_ov002_02207f3c(Object *p, int a);
extern void func_0200277c(int a);
extern void func_0200284c(int a, int b, int c);
extern void func_ov122_0229efc8(Object *p, int a);
extern void func_ov002_02207e80(Object *p, int a, int b, int c);
extern int func_ov002_02207f60(Object *p);

void func_ov122_022a1bd4(Object *p)
{
    if (func_ov002_02207f3c(p, 0) != 0) {
        func_0200277c(6);
        func_0200284c(6, 0, 0);
        func_ov122_0229efc8(p, 1);
        p->unk_8C = p->unk_B5;
    } else {
        func_ov002_02207e80(p, 6, 0, 0);
        p->unk_94 = func_ov002_02207f60(p);
    }
}
