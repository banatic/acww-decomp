/* func_ov107_0229ddc4 @ 0x0229ddc4, 0x90 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov107_0229db24(void *p);
extern void func_ov002_0220ab84(void *p, int x);
extern void func_ov094_0229ad20(void *p);
extern void func_ov107_0229d224(void *p);
extern void func_ov094_0229b2b0(void *p);
extern void func_ov094_0229b794(void *p, int x);
extern void func_ov002_02207f20(void *p, int a, int b, int c, int d);
extern void func_02002708(int x);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern void func_ov002_02208090(void *p, int x);
extern void func_ov107_0229c2a4(void *p, int x);
extern int func_ov002_02207f60(void *p);

struct UnkStruct_0229ddc4 {
    char pad_00[0x98];
    int unk_98;
    char pad_9C[0x10c - 0x9c];
    char unk_10C;
    char pad_10D[0xb6c - 0x10d];
    char unk_B6C;
    char pad_B6D[0x2828 - 0xb6d];
    char unk_2828;
};

void func_ov107_0229ddc4(struct UnkStruct_0229ddc4 *p)
{
    func_ov107_0229db24(p);
    func_ov002_0220ab84(&p->unk_2828, 0x65);
    func_ov094_0229ad20(&p->unk_10C);
    func_ov107_0229d224(p);
    func_ov094_0229b2b0(&p->unk_B6C);
    func_ov094_0229b794(&p->unk_B6C, 0xf);
    func_ov002_02207f20(p, 8, 0, 0, 0x30);
    func_02002708(6);
    func_ov002_02207e80(p, 6, 0, -16);
    func_ov002_02208090(p, 2);
    func_ov107_0229c2a4(p, 1);
    func_ov107_0229c2a4(p, 2);
    p->unk_98 = func_ov002_02207f60(p);
}
