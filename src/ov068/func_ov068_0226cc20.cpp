/* func_ov068_0226cc20 @ 0x0226cc20, 0x90 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0226cc20_2 {
  public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual int method();
};

typedef struct {
    char pad_00[0xf4];
    int unk_F4;
} UnkStruct_0226cc20;

extern "C" {
int func_02096190(int);
int func_0207d18c(int, int);
int func_020b6640(int);
int func_0201c390(UnkStruct_0226cc20_2 *, int);
int func_0201c2b0(UnkStruct_0226cc20_2 *, int);
extern signed short data_ov068_02278264[];

int func_ov068_0226cc20(UnkStruct_0226cc20 *p, UnkStruct_0226cc20_2 *obj)
{
    int f;
    int flag;
    int result;
    int a, b;
    signed short d;
    int t;

    f = func_02096190(4);

    if (obj->method()) {
        t = func_0207d18c(obj->method(), 0);
    } else {
        t = 0;
    }
    if (t) {
        flag = 1;
    } else {
        flag = 0;
    }

    result = 0;
    if (func_020b6640(0) == 0) {
        if (p->unk_F4 <= 0 && flag != 0 && f != 0) {
            a = func_0201c390(obj, f);
            if (a <= 0x7000) {
                b = func_0201c2b0(obj, f);
                d = data_ov068_02278264[0];
                if (b >= -d && b <= d) {
                    result = 1;
                }
            }
        }
    }
    return result;
}
}
