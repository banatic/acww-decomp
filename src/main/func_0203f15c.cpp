/* func_0203f15c @ 0x0203f15c, 0x104 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0203f15c_2 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual int v18(int x);
    virtual void v19(int a, unsigned char b);
    virtual void v20();
    virtual int v21(int x);
    virtual int v22(int x);
};

struct UnkStruct_0203f15c {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
    unsigned char unk_03;
    unsigned char unk_04;
    unsigned char unk_05;
};

extern "C" {
extern UnkStruct_0203f15c_2 *func_0203ef90(int);
extern int func_020961a8(int);
extern int func_02073918(void *, int);
extern void func_0203f490(int, int);
extern void *data_020ccf94;
extern unsigned char data_020dab94;
}

extern "C" void func_0203f15c(UnkStruct_0203f15c *p, int arg)
{
    unsigned int sel = p->unk_05;
    UnkStruct_0203f15c_2 *o = func_0203ef90(p->unk_01 | (p->unk_02 << 8) | (p->unk_03 << 16) | (p->unk_04 << 24));
    int r = func_020961a8(arg);
    if (o == 0 || r == 0) {
        if (p->unk_00 == 4) {
            if (func_02073918(data_020ccf94, arg) == 0) {
                func_0203f490(2, arg);
            } else {
                data_020dab94 = 2;
            }
        }
    } else {
        if (p->unk_00 == 5) {
            o->v19(sel, (unsigned char) arg);
        } else {
            int st = 0;
            switch (sel) {
                case 0:
                    st = o->v18(r);
                    break;
                case 5:
                    st = o->v21(r);
                    break;
                case 1:
                    st = o->v22(r);
                    break;
            }
            if (func_02073918(data_020ccf94, arg) == 0) {
                if (st != 0) {
                    o->v19(3, (unsigned char) arg);
                    func_0203f490(1, arg);
                } else {
                    func_0203f490(2, arg);
                }
            } else {
                if (st != 0) {
                    o->v19(3, 4);
                    data_020dab94 = 1;
                } else {
                    data_020dab94 = 2;
                }
            }
        }
    }
}
