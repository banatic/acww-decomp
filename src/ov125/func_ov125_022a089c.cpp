/* func_ov125_022a089c @ 0x022a089c, 0xcc bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

struct Blk {
    char pad_00[4];
};
struct UnkStruct_022a089c {
    char pad_00[4];
    unsigned short tile : 10;
    unsigned short attr : 6;
};

struct UnkStruct_022a089c_2 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

struct UnkStruct_022a089c_3 {
    char pad_00[0x94];
    Blk unk_94;
    char pad_98[0x4dc];
    UnkStruct_022a089c_2 unk_574;
    char pad_578[0xcc];
    Blk unk_644;
    char pad_648[0x60];
    Blk unk_6A8;
    char pad_6AC[0x1c8];
    int unk_874;
};

extern "C" {
extern int func_ov125_0229f76c(UnkStruct_022a089c_3 *, int);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(Blk *);
extern int func_ov002_02207f60(UnkStruct_022a089c_3 *);
extern void func_ov002_0220ad18(Blk *, int);
extern void func_ov124_0229ef08(Blk *, int, int);
extern int func_ov125_0229fe40(UnkStruct_022a089c_3 *, unsigned char);
extern int func_ov125_0229fe4c(UnkStruct_022a089c_3 *, unsigned char);
extern void func_020896b8(int, UnkStruct_022a089c *, int, int, int, int, int);
extern UnkStruct_022a089c data_ov125_022a0a28;
}

extern "C" int func_ov125_022a089c(UnkStruct_022a089c_3 *obj)
{
    int base;
    int t;
    int zero;
    unsigned char j;
    int i;

    base = obj->unk_874;
    if (func_ov125_0229f76c(obj, 1) == 0) {
        return 0;
    }
    obj->unk_574.v2();
    if (func_0206fe54() != 0) {
        func_ov002_02209eb8(&obj->unk_644);
    }
    func_ov002_0220ad18(&obj->unk_6A8, func_ov002_02207f60(obj));
    func_ov124_0229ef08(&obj->unk_94, 0, base);
    j = 0;
    i = 0;
    zero = 0;
    for (; i < 8; i++) {
        data_ov125_022a0a28.tile = (unsigned short) (i * 4 + 0xc0);
        t = base + func_ov125_0229fe40(obj, j);
        func_020896b8(1, &data_ov125_022a0a28, func_ov125_0229fe4c(obj, j), t, i + 5, 2, zero);
        j = j + 1;
    }
    return 1;
}
