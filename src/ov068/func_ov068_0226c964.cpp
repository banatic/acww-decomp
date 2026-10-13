/* func_ov068_0226c964 @ 0x0226c964, 0xc8 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0226c964 {
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

struct Flags {
    unsigned char pad_00[0x1d];
    unsigned char b0 : 1;
    unsigned char b1 : 1;
};

extern "C" Flags *func_0207f270(int);
extern "C" int func_020984e8(void);
extern "C" int func_02099020(int, int);
extern "C" void func_0209e474(int *);
extern "C" int func_0208150c(int);
extern "C" int func_020036e8(int);
extern "C" int func_020821d4(int, int *);
extern "C" int func_02003704(int);
extern "C" int func_020794cc(Flags *);
extern "C" int func_ov068_0226ca2c(void *);
extern "C" void func_02013948(void *, void *, int, int, UnkStruct_0226c964 *);

extern "C" void func_ov068_0226c964(char *self, int a, UnkStruct_0226c964 *obj)
{
    int v;
    int st;
    int w;
    int local[2];
    int ok;
    int t;

    v = obj->v25();
    st = 7;
    if (v != 0) {
        if (func_0207f270(v)->b1) {
            st = 3;
        } else {
            t = func_020984e8();
            if (t != 0) {
                w = func_02099020(t, 1);
            } else {
                w = 0;
            }
            local[0] = 0;
            local[1] = 0;
            func_0209e474(local);
            ok = (w != 0) ? 1 : 0;
            if (ok == 0) {
                if (func_020821d4(func_020036e8(func_0208150c(v)), local) != 0) {
                    st = 3;
                    goto out;
                }
            }
            w = 7;
            if (func_02003704(func_0208150c(v)) != 0) {
                if (func_0207f270(v) != 0) {
                    w = func_020794cc(func_0207f270(v));
                }
            }
            if (w == 6) {
                st = 6;
            }
        }
    }
out:
    if (st == 7) {
        st = func_ov068_0226ca2c(self);
    }
    func_02013948(self + 0x3c, (char *) obj + 0x5c, st, a, obj);
}
