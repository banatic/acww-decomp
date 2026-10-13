/* func_ov068_0226c6ac @ 0x0226c6ac, 0xa8 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0226c6ac {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual void f5();
    virtual void f6();
    virtual void f7();
    virtual void f8();
    virtual void f9();
    virtual void f10();
    virtual void f11();
    virtual void f12();
    virtual void f13();
    virtual void f14();
    virtual void f15();
    virtual void f16();
    virtual void f17();
    virtual void f18();
    virtual void f19();
    virtual void f20();
    virtual void f21();
    virtual void f22();
    virtual void f23();
    virtual void f24();
    virtual int v25();
};

struct Vec {
    int x, y, z;
};

struct Flags {
    unsigned char pad_00[0x1d];
    unsigned char b0 : 1;
    unsigned char b1 : 1;
};

extern "C" Flags *func_0207f270(int);
extern "C" int func_02013300(void *);
extern "C" int func_02013894(void *);
extern "C" int func_020132a0(void *, Vec *);
extern "C" void func_ov068_0226c964(void *, int, UnkStruct_0226c6ac *);

extern "C" int func_ov068_0226c6ac(char *self, Vec *out, UnkStruct_0226c6ac *obj)
{
    if (obj->v25() != 0) {
        if (func_0207f270(obj->v25())->b1) {
            if (func_02013300(self + 0x3c) != 3) {
                *(short *) (self + 0xd8) = 0;
            }
        }
    }
    if (func_02013894(self + 0x3c) == 0 || *(short *) (self + 0xd8) == 0) {
        func_ov068_0226c964(self, 0, obj);
        *(short *) (self + 0xd8) = -1;
        *(short *) (self + 0xda) = 0;
    }
    {
        Vec *s = (Vec *) ((char *) obj + 0x5c);
        out->x = s->x;
        out->y = s->y;
        out->z = s->z;
    }
    if (func_020132a0(self + 0x3c, out) != 0) {
        if (*(short *) (self + 0xd8) == -1) {
            *(short *) (self + 0xd8) = 0x1770;
        }
    }
    return 1;
}
