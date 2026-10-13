/* func_ov045_02260e94 @ 0x02260e94, 0xf0 bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02260e94_2 {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void v14(int);
};
struct UnkStruct_02260e94;
typedef int (UnkStruct_02260e94::*PMF)(void);
struct UnkStruct_02260e94_3 {
    int a;
    int b;
    PMF fn;
};
struct UnkStruct_02260e94 {
    char pad_00[0x190];
    unsigned int lo : 12;
    unsigned int mid : 16;
    unsigned int hi : 4;
    char pad_194[0x2e4];
    char unk_478[0xec];
    char unk_564[0xf0];
    int unk_654;
    int unk_658;
    char pad_65C[0x30];
    UnkStruct_02260e94_2 sub68c;
    char pad_690[0xc8];
    unsigned char unk_758;
};
extern "C" {
extern int func_02019df8(void *);
extern int func_02019de8(void *);
extern int func_020912d4(int, void *, int, int);
extern int func_020e8858(void *);
extern void func_0209129c(int);
extern void func_02091278(int, void *, int, int);
}
extern UnkStruct_02260e94_3 data_ov045_022615bc[];

extern "C" int func_ov045_02260e94(UnkStruct_02260e94 *s)
{
    int t;
    int r;

    t = func_02019df8(&s->unk_564);
    if (t == 0x1e || t == 0x20) {
        if (func_02019de8(&s->unk_564) != 0) {
            s->sub68c.v14(0);
        }
    }
    if (s->unk_654 == -1) {
        if (t == 0x21) {
            if (s->mid >= 0x12) {
                s->unk_654 = func_020912d4(0x3d, s->unk_478, 0, 0);
                s->unk_758 = 0x16;
            }
        }
    } else if (func_020e8858(&s->unk_758) == 0) {
        func_0209129c(s->unk_654);
        s->unk_654 = -1;
    } else {
        func_02091278(s->unk_654, s->unk_478, 0, 0);
    }
    r = 0;
    if (data_ov045_022615bc[s->unk_658].fn != 0) {
        r = (s->*(data_ov045_022615bc[s->unk_658].fn))();
    }
    return r;
}
