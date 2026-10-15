/* func_020edfcc @ 0x020edfcc, 0xd8 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

struct Node {
    char pad_00[4];
    int unk_04;
};

struct UnkStruct_020edfcc {
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
    virtual void v13();
    virtual void v14();
    virtual int v15();
    char pad_04[0x48];
    Node *unk_4C;
};

extern "C" {
extern Node *func_020e99d8(void *, int);
extern int func_020e9ed4(Node *, int, int);
extern int func_020e9e34(Node *);
extern void func_020e9974(void);
extern void func_020e9fd4(Node *);
extern void func_020ee470(UnkStruct_020edfcc *);
}

extern "C" int func_020edfcc(UnkStruct_020edfcc *a, void *b, int c)
{
    Node *n;
    int ok;
    int had;

    if (a->unk_4C != 0) {
        return 1;
    }
    if (b != 0) {
        n = func_020e99d8(b, c);
        if (n != 0) {
            had = n->unk_04 & 0x10;
            if (had != 0) {
                func_020e9ed4(n, 0x10, 0x10);
            }
            ok = a->v15();
            if (had == 0) {
                if (func_020e9ed4(n, 0x10, 0x10) == 0) {
                    ok = 0;
                }
            }
            func_020e9e34(n);
            func_020e9974();
            if (ok == 0) {
                func_020e9fd4(n);
            } else {
                a->unk_4C = n;
                return 1;
            }
        }
    }
    func_020ee470(a);
    return 0;
}
