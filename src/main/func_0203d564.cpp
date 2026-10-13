/* func_0203d564 @ 0x0203d564, 0x104 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0203d564 {
    char pad_00[0x5c];
    char unk_5C[0x30c - 0x5c];
    char unk_30C[0x50c - 0x30c];
    int unk_50C;
};

struct UnkStruct_0203d564_2 {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual int m3();
    char unk_04[0x1e - 4];
    char unk_1E;
};

extern "C" int func_0203d4d8(UnkStruct_0203d564_2 *);
extern "C" void func_02064328(char *, const char *, ...);
extern "C" int func_020a9a08(char *, char *);
extern "C" int func_020a9938(char *, char *);
extern "C" void func_020a99d8(char *);
extern "C" int *func_0203d4c0(UnkStruct_0203d564_2 *);
extern "C" int func_0203d4c4(UnkStruct_0203d564_2 *);
extern "C" int func_0203d4e8(UnkStruct_0203d564_2 *);
extern "C" int func_0203dd10(UnkStruct_0203d564 *, int);
extern "C" int func_020a89f8(int, char *);
extern "C" int func_020a8be4(int, char *);
extern const char data_020da9c8[];
extern const char data_020da9d8[];

extern "C" int func_0203d564(UnkStruct_0203d564 *p, UnkStruct_0203d564_2 *q)
{
    char buf[0x44];
    int x;
    int ok;
    int a;
    int *b;
    int c;

    x = func_0203d4d8(q);
    if (x) {
        func_02064328(buf, data_020da9c8, q->m3(), x, q->unk_04);
    } else {
        func_02064328(buf, data_020da9d8, q->m3(), q->unk_04);
    }
    ok = func_020a9a08(p->unk_5C, buf);
    ok &= ok ? func_020a9938(p->unk_5C, &q->unk_1E) : 0;
    ok = ok != 0;
    func_020a99d8(p->unk_5C);
    if (ok) {
        a = func_0203d4c4(q);
        b = func_0203d4c0(q);
        c = func_0203d4e8(q);
        ok &= func_0203dd10(p, b != 0);
        ok = ok != 0;
        if (c) {
            ok &= func_020a89f8(a, p->unk_30C);
            ok = ok != 0;
        } else {
            ok &= func_020a8be4(a, p->unk_30C);
            ok = ok != 0;
        }
        if (b) {
            *b = p->unk_50C;
        }
    }
    return ok;
}
