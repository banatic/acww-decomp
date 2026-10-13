/* func_020b4344 @ 0x020b4344, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020b4344_4 {
    char pad_00[4];
};
struct UnkStruct_020b4344 {
    char pad_00[0xc];
};

extern "C" {
extern int func_02064328(char *, const char *, ...);
extern int func_020a9a08(UnkStruct_020b4344_4 *, char *);
extern int func_020a9938(UnkStruct_020b4344_4 *, void *);
extern void func_020a99d8(UnkStruct_020b4344_4 *);
extern int func_020a8be4(void *, UnkStruct_020b4344 *);
extern void func_020a9b1c(void *, UnkStruct_020b4344 *);
extern const char data_020e52dc[];
}

struct UnkStruct_020b4344_2 {
    char pad_00[0x4c];
    UnkStruct_020b4344_4 sub4c;
    char pad_50[0xaa0];
    UnkStruct_020b4344 unk_AF0;
    UnkStruct_020b4344 unk_AFC;
};

extern "C" bool func_020b5350(UnkStruct_020b4344_2 *, unsigned char, unsigned char);

struct Blk {
    char pad_00[8];
    char unk_08[4];
};

struct UnkStruct_020b4344_3 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int v3();
    char unk_04[0x1a];
    char unk_1E[6];
    Blk *unk_24;
    unsigned char unk_28;
    unsigned char unk_29;
};

extern "C" int func_020b4344(UnkStruct_020b4344_2 *a, UnkStruct_020b4344_3 *b)
{
    char buf[0x44];
    int ok;
    Blk *p;

    func_02064328(buf, data_020e52dc, b->v3(), b->unk_04);
    ok = func_020a9a08(&a->sub4c, buf);
    ok = (ok & (ok ? func_020a9938(&a->sub4c, b->unk_1E) : 0)) != 0;
    func_020a99d8(&a->sub4c);
    if (ok) {
        p = b->unk_24;
        ok = (ok & func_020b5350(a, b->unk_28, b->unk_29)) != 0;
        if (p != 0) {
            ok = (ok & func_020a8be4(p, &a->unk_AFC)) != 0;
            func_020a9b1c(p->unk_08, &a->unk_AF0);
        }
    }
    return ok;
}
