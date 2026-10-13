/* func_ov133_0229c340 @ 0x0229c340, 0x5c bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207f20(void *p, int a, int b, int c, int d);
extern void func_02002708(int x);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern void func_ov133_0229ad78(void *p, int x);
extern int func_ov002_02207f60(void *p);
extern void func_ov002_02208090(void *p, int x);

struct Type {
    char pad_00[0x94];
    int unk_94;
};

void func_ov133_0229c340(struct Type *p)
{
    func_ov002_02207f20(p, 0xa, 0, 0, 0x30);
    func_02002708(4);
    func_ov002_02207e80(p, 4, 0, 0);
    func_02002708(6);
    func_ov002_02207e80(p, 6, 0, 0);
    func_ov133_0229ad78(p, 1);
    p->unk_94 = func_ov002_02207f60(p);
    func_ov002_02208090(p, 2);
}
