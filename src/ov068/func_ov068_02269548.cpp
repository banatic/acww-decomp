/* func_ov068_02269548 @ 0x02269548, 0x13c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02269548 {
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
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void *v25();
    char pad0[0x34c];
    char unk_350[4];
    char pad1[0x210];
    char sub[4];
    char pad2[0x49e];
    unsigned short unk_A06;
};
struct St {
    char pad0[0x1c];
    unsigned char unk_1C;
    char pad1[3];
    int unk_20;
    char pad2[0xc0];
    char *unk_E4;
    char pad_E8[0xc];
    int unk_F4;
};
extern "C" {
extern int func_ov068_022697cc(St *, UnkStruct_02269548 *, int);
extern void func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);
extern void func_ov068_0226cce8(St *, UnkStruct_02269548 *, int);
extern int func_ov068_0226c0e0(St *, UnkStruct_02269548 *);
extern int func_ov068_02269814(St *, UnkStruct_02269548 *);
extern void func_0201b044(void *, void *);
extern void func_0207d148(void *);
extern void func_0207d0f0(void *, int);
extern unsigned short data_020c80f8;
extern const short data_ov068_02276724[];
}

extern "C" void func_ov068_02269548(St *s, UnkStruct_02269548 *o)
{
    void *x = &o->unk_350;
    if (s->unk_E4 != 0) {
        if (func_ov068_022697cc(s, o, 0x3000) != 0) {
            func_02019d0c(&o->sub, 0xb, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
            s->unk_1C = 2;
            s->unk_20 = 0xc8;
        } else if (o->unk_A06 >= data_ov068_02276724[0]) {
            func_ov068_0226cce8(s, o, 0x15);
        } else if (func_ov068_0226c0e0(s, o) != 0) {
            func_ov068_0226cce8(s, o, 0x13);
        } else if (s->unk_20 == 0) {
            func_ov068_0226cce8(s, o, 0);
            s->unk_F4 = 0x4b0;
            if (o->v25() != 0) {
                func_0207d148(o->v25());
            }
        } else if (func_ov068_02269814(s, o) != 0) {
            func_0201b044(x, s->unk_E4 + 0x5c);
        } else {
            func_ov068_0226cce8(s, o, 0);
            s->unk_F4 = 0x4b0;
            if (o->v25() != 0) {
                func_0207d148(o->v25());
            }
        }
    } else {
        func_ov068_0226cce8(s, o, 0);
        s->unk_F4 = 0x4b0;
        if (o->v25() != 0) {
            func_0207d0f0(o->v25(), -1);
        }
    }
}
