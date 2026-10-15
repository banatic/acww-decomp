/* func_ov004_0220c930 @ 0x0220c930, 0xc4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0220c930 {
  public:
    virtual void v00() = 0;
    virtual void v01() = 0;
    virtual void v02() = 0;
    virtual void v03() = 0;
    virtual void v04() = 0;
    virtual void v05() = 0;
    virtual void v06() = 0;
    virtual void v07() = 0;
    virtual void v08() = 0;
    virtual void v09() = 0;
    virtual void v10() = 0;
    virtual void v11() = 0;
    virtual void v12() = 0;
    virtual void v13() = 0;
    virtual void v14() = 0;
    virtual void v15() = 0;
    virtual void v16() = 0;
    virtual void v17() = 0;
    virtual void v18() = 0;
    virtual void v19() = 0;
    virtual void v20() = 0;
    virtual void v21() = 0;
    virtual void v22() = 0;
    virtual void v23() = 0;
    virtual void v24() = 0;
    virtual void v25() = 0;
    virtual void v26() = 0;
    virtual void v27() = 0;
    virtual void v28() = 0;
    virtual void v29() = 0;
    virtual void v30() = 0;
    virtual void v31() = 0;
    virtual void v32() = 0;
    virtual void v33() = 0;
    virtual void v34() = 0;
    virtual void v35() = 0;
    virtual void v36() = 0;
    virtual void v37() = 0;
    virtual void vf(int) = 0;

    char pad_04[0x8e - 4];
    short unk_8E;
    char pad_90[0x16c - 0x90];
    short unk_16C;
    char pad_16E[0x288 - 0x16e];
    unsigned char unk_288;
    char pad_289[0x788 - 0x289];
    int unk_788;
};

struct Pair {
    int a;
    int b;
};

struct UnkStruct_0220c930_2 {
    unsigned char data[0x24];
};

extern "C" {
int func_ov004_0220d594(void *p, UnkStruct_0220c930 *self);
void func_ov004_0220ee90(UnkStruct_0220c930 *self, int a, int b);
char *func_ov004_0220db94(UnkStruct_0220c930_2 *l);
void func_ov004_0220f27c(UnkStruct_0220c930 *self, UnkStruct_0220c930_2 *l, int a, int b);
unsigned int func_ov004_0220db68(UnkStruct_0220c930_2 *l);
Pair *func_ov004_0220db5c(UnkStruct_0220c930_2 *l, unsigned int i);
UnkStruct_0220c930 *func_ov004_0223cd50(void);
UnkStruct_0220c930 *func_ov004_0223cc10(UnkStruct_0220c930 *obj, int a, int b, int c);
void func_ov004_0220db90(UnkStruct_0220c930_2 *l);
}

extern "C" int func_ov004_0220c930(UnkStruct_0220c930 *self)
{
    short d;
    unsigned int i;
    UnkStruct_0220c930 *obj;
    Pair *p1;
    Pair *p2;
    UnkStruct_0220c930 *res;
    UnkStruct_0220c930_2 local;

    func_ov004_0220d594((char *) self + 0x18c, self);
    d = (short) (self->unk_16C - self->unk_8E);
    func_ov004_0220ee90(self, 0, d);
    if (d < 0) {
        d = 1;
    } else {
        d = 0;
    }
    self->vf(d);

    if (self->unk_288 != 0) {
        goto exit;
    }
    if (self->unk_788 != 1) {
        goto exit;
    }

    func_ov004_0220db94(&local);
    func_ov004_0220f27c(self, &local, 0, 0);

    i = 0;
    while (i < func_ov004_0220db68(&local)) {
        obj = func_ov004_0223cd50();
        p1 = func_ov004_0220db5c(&local, i);
        p2 = func_ov004_0220db5c(&local, i);
        res = func_ov004_0223cc10(obj, p1->a, p2->b, 1);
        if (res != 0) {
            res->vf(d);
        }
        i++;
    }

    func_ov004_0220db90(&local);

exit:
    return 1;
}
