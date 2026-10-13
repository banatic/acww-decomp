/* func_02038444 @ 0x02038444, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02038444 {
    char b[6];
};
struct Blk {
    char pad_00[4];
};

struct UnkStruct_02038444_3 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void *v3();
};

struct UnkStruct_02038444_2 {
    char pad_00[0xe0];
    int unk_E0;
    int unk_E4;
    UnkStruct_02038444_3 unk_E8;
    char pad_EC[0x110];
    Blk unk_1FC;
    char pad_200[0x50];
    Blk unk_250;
};

extern "C" {
extern void func_020a8c1c(Blk *);
extern void *func_020a7bf4(void *, int);
extern void func_020a8a34(Blk *, void *);
extern int func_020a8f74(Blk *);
extern void func_020a89f8(Blk *, void *);
extern void func_020a89dc(Blk *, Blk *);
extern void *func_02038b80(void);
extern UnkStruct_02038444 data_020da4d0;
extern unsigned char data_021c5934;
}

extern "C" void func_02038444(UnkStruct_02038444_2 *a, int b, int c)
{
    void *h;

    func_020a8c1c(&a->unk_250);
    a->unk_E0 = 0;
    h = func_020a7bf4(a->unk_E8.v3(), b);
    if (h != 0) {
        func_020a8a34(&a->unk_250, h);
        if (a->unk_E4 >= 0 && b == 3) {
            a->unk_E0 = func_020a8f74(&a->unk_250);
            UnkStruct_02038444 s = data_020da4d0;
            func_020a89f8(&a->unk_250, &s);
            func_020a89dc(&a->unk_250, &a->unk_1FC);
        }
        if (c != 0 && b == 3 && data_021c5934 != 0) {
            func_020a89f8(&a->unk_250, func_02038b80());
        }
    }
}
