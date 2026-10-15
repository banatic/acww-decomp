/* func_ov100_0229cbd4 @ 0x0229cbd4, 0x68 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
int func_ov100_0229cc70(void *p);
int func_ov100_0229cc60(void *p);
void func_ov002_0220a05c(void *p, int a, int b, int c, int d);
unsigned char *func_ov002_02208098(void *object, unsigned char value);
int func_ov100_0229c2c0(void *p, int a);
void func_ov100_0229c2a0(void *p, int a);
}

class UnkStruct_0229cbd4 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

struct UnkStruct_0229cbd4_2 {
    char pad_00[0x8d];
    unsigned char unk_8D;
    char pad_8E[0x2274 - 0x8e];
    UnkStruct_0229cbd4 member;
    char pad_2278[0x2924 - (0x2274 + 4)];
    unsigned char unk_2924;
};

extern "C" void func_ov100_0229cbd4(struct UnkStruct_0229cbd4_2 *p)
{
    int v1 = func_ov100_0229cc70(p);
    int v2 = func_ov100_0229cc60(p);
    func_ov002_0220a05c(&p->member, v1, v2, 3, 1);
    p->unk_2924 = p->unk_8D;
    func_ov002_02208098((void *) (p), 8);
    if (func_ov100_0229c2c0(p, 0x100) != 0) {
        p->member.f3();
        func_ov100_0229c2a0(p, 0x100);
    }
}
