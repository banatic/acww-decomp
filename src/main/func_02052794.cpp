/* func_02052794 @ 0x02052794, 0x140 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02052794 {
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
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual int v29(int);
};
struct Bits {
    unsigned int f0 : 6;
    unsigned int f6 : 1;
    unsigned int f7 : 1;
    unsigned int f8 : 4;
    unsigned int f12 : 4;
    unsigned int f16 : 5;
    unsigned int f21 : 8;
    unsigned int f29 : 1;
    unsigned int f30 : 1;
    unsigned int f31 : 1;
};
extern "C" {
extern void *func_ov004_0223cd50(void);
extern UnkStruct_02052794 *func_ov004_0223cc10(void *, int, int, int);
extern int func_02073d90(void *);
extern int func_ov004_0220e5c8(UnkStruct_02052794 *);
extern int func_020b65c4(void);
extern int func_ov004_0220e5b8(UnkStruct_02052794 *);
extern void func_02073820(void *);
extern void func_020737f0(void *, void *, int);
extern void func_02073770(void *, int, int);
extern void *data_020ccf94;
}

extern "C" int func_02052794(int a1, int a2, int a3, int a4, unsigned char a5, unsigned char a6, int a7)
{
    Bits b;
    UnkStruct_02052794 *o;
    void *h;
    int t;
    int flag;

    if (a7 == 4) {
        flag = 0;
    } else {
        flag = 1;
    }
    o = func_ov004_0223cc10(func_ov004_0223cd50(), a1, a2, a3);
    if (o == 0) {
        return 0;
    }
    if (func_02073d90(data_020ccf94) != 0 && o != 0 && func_ov004_0220e5c8(o) == 0) {
        t = o->v29(a4);
        b.f0 = func_020b65c4();
        b.f6 = a3;
        b.f7 = t;
        b.f8 = a1;
        b.f12 = a2;
        b.f16 = a4;
        b.f21 = a5;
        b.f31 = a6;
        b.f29 = flag;
        b.f30 = func_ov004_0220e5b8(o);
        h = data_020ccf94;
        func_02073820(h);
        func_020737f0(h, &b, 4);
        func_02073770(h, 0x18, a7);
    }
    return 1;
}
