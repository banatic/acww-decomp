/* func_020698d4 @ 0x020698d4, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

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
extern void func_0206b964(void *, unsigned char *);
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
