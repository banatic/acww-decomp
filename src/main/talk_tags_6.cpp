/* talk_tags_6: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02069960 @ 0x02069960, 0x60 bytes, Thumb
 * func_020698d4 @ 0x020698d4, 0x8c bytes, Thumb
 */

class UnkStruct_02069960 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual void f5();
    virtual void f6();
    virtual void f7();
    virtual void f8();
    virtual void f9();
    virtual void f10();
    virtual void f11();
    virtual void f12();
    virtual void target(int a, int b);
};

struct UnkStruct_02069960_2 {
    char pad_00[0x14a8];
    UnkStruct_02069960 *obj;
};

struct UnkStruct_02069960_3 {
    char pad_00[0x24];
    UnkStruct_02069960_2 *inner;
    char pad_28[0x10];
    unsigned char unk_38;
};

extern "C" unsigned int func_020a86e4(void *a, unsigned char *b, unsigned char *c, unsigned char *d);
extern "C" unsigned int func_0203cc04(void);
extern "C" void func_0206b964(void *self, unsigned char *arr);

struct UnkStruct_020698d4 {
    char unk_00;
};

struct Big {
    char pad_00[0x9284];
    UnkStruct_020698d4 sub;
};

extern "C" {
extern void func_020a86a4(void *, unsigned char *, unsigned char *, unsigned char *, unsigned char *);
extern int func_0207cad4(UnkStruct_020698d4 *);
extern int data_020cd40c;
extern Big data_021dc7a8;
}

struct UnkStruct_020698d4_2 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13(int, int);
};

struct UnkStruct_020698d4_3 {
    char pad_00[0x14a8];
    UnkStruct_020698d4_2 *unk_14A8;
};

struct UnkStruct_020698d4_4 {
    char pad_00[0x24];
    UnkStruct_020698d4_3 *unk_24;
    char pad_28[0x10];
    char unk_38;
};

extern "C" void func_02069960(UnkStruct_02069960_3 *self)
{
    unsigned char arr[4];
    int idx;
    UnkStruct_02069960 *obj;
    unsigned int x;

    obj = self->inner->obj;
    obj->target(6, 3);
    x = (func_020a86e4((void *) &self->unk_38, &arr[1], &arr[2], &arr[3]), func_0203cc04());
    if (x == 0x38) {
        idx = 2;
    } else if (x >= 0x21) {
        idx = 1;
    } else {
        idx = 0;
    }
    arr[0] = (arr + 1)[idx];
    func_0206b964(self, arr);
}

extern "C" void func_020698d4(UnkStruct_020698d4_4 *obj)
{
    unsigned char c;
    unsigned char b[4];
    int x;
    int n;
    int k;
    Big *bp;

    obj->unk_24->unk_14A8->v13(7, 4);
    func_020a86a4(&obj->unk_38, &b[0], &b[1], &b[2], &b[3]);
    bp = &data_021dc7a8;
    x = bp ? func_0207cad4(&bp->sub) : 0;
    n = data_020cd40c;
    if (x <= n) {
        k = 0;
    } else if (x == n + 1) {
        k = 1;
    } else if (x >= 8) {
        k = 3;
    } else {
        k = 2;
    }
    c = b[k];
    func_0206b964(obj, &c);
}
