/* func_0202ec58 @ 0x0202ec58, 0x170 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;

struct UnkStruct_0202ec58 {
    virtual int f0();
    virtual int f1();
    virtual int f2();
    virtual int f3();
    virtual int f4();
    virtual int f5();
    virtual int f6();
    virtual int f7();
    virtual int f8();
    virtual int f9();
    virtual int f10();
    virtual int f11();
    virtual int f12();
    virtual int f13();
    virtual int f14();
    virtual int f15();
    virtual int f16();
    virtual int f17();
    virtual int f18();
    virtual int f19();
    virtual int f20();
    virtual int f21();
    virtual int f22();
    virtual int f23();
    virtual int f24();
    virtual int f25();
    virtual int f26();
    virtual int f27();
    virtual int f28();
    virtual int f29();
    virtual int f30();
    virtual int f31();
    virtual int f32();
    virtual int f33();
    virtual int f34();
    virtual int f35();
    virtual int f36();
    virtual int f37();
    virtual int f38();
    virtual int f39();
    virtual int f40();
    virtual int f41();
    virtual int f42();
};

#define B(o, n) (*(unsigned char *) ((char *) (o) + (n)))
#define S(o, n) (*(short *) ((char *) (o) + (n)))
#define W(o, n) (*(int *) ((char *) (o) + (n)))
#define P(o, n) ((void *) ((char *) (o) + (n)))

extern void *data_020ccf94;
extern "C" int func_0201bd48(void *o);
extern "C" int func_020a7278(void);
extern "C" int func_02073d90(void *g);
extern "C" int func_0201bee0(void *o, Vec *v, short *s);
extern "C" int func_020eaa2c(Vec *v, void *p);
extern "C" int func_02082f04(void *p);
extern "C" int func_0208308c(void *p);
extern "C" int func_0202ee10(void *o);
extern "C" int func_0201a304(void *a, void *o);
extern "C" int func_0201691c(void *a, void *o, int r);
extern "C" void func_02019e04(void *a, void *o, int c, int d, int e, int f, int g, int h, int i);
extern "C" int func_0201c444(void *o);
extern "C" void func_02089c20(void *a, void *o, int c, int d, int e, int f, int g, int h, int i);
extern "C" int func_02082554(void *o, void *p);
extern "C" void func_02013c0c(void *p);

extern unsigned char data_021fbee8[];

extern "C" int func_0202ec58(void *o)
{
    short s;
    Vec v;
    int r;

    if (func_0201bd48(o) == 0) {
        return 0;
    }
    if (func_020a7278() == 0 && func_02073d90(data_020ccf94) != 0 && B(o, 0x563) == 0) {
        v.x = 0;
        v.y = 0;
        v.z = 0;
        s = 0;
        if (func_0201bee0(o, &v, &s) != 0 && func_020eaa2c(&v, (void *) data_021fbee8) != 0) {
            Vec *p = (Vec *) P(o, 0x5c);
            W(o, 0x5c) = v.x;
            p->y = v.y;
            p->z = v.z;
            S(o, 0x8e) = s;
            S(o, 0x94) = s;
        }
    }
    if (func_02082f04(P(o, 0x640)) == 0) {
        if (func_0208308c(P(o, 0x640)) == 0) {
            return 0;
        }
        if (func_0202ee10(o) == 0) {
            return 0;
        }
    }
    if (func_0201a304(P(o, 0x2ac), o) == 0) {
        return 0;
    }
    r = ((UnkStruct_0202ec58 *) o)->f42();
    if (func_0201691c(P(o, 0x334), o, r) == 0) {
        return 0;
    }
    func_02019e04(P(o, 0x564), o, 0, 1, 0, 0, 0, 0, 0);
    func_02089c20(P(o, 0x4cc), o, W(o, 0x648), W(o, 0x64c), 8, 0x2fc, 3, (unsigned char) func_0201c444(o), 0x1000);
    if (func_02082554(o, P(o, 0xea)) == 0) {
        return 0;
    }
    func_02013c0c(P(o, 0x558));
    return 1;
}
