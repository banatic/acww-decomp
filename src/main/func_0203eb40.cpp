/* func_0203eb40 @ 0x0203eb40, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0203eb40_2 {
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
    virtual int m(int a);
};

struct UnkStruct_0203eb40 {
    char pad_00[0x10];
    int unk_10;
    char pad_14[1];
    unsigned char unk_15;
    unsigned char unk_16;
    unsigned char unk_17;
};

extern "C" {
extern void *data_020ccf94;
int func_0203f338(void);
int func_02073d90(void *a);
UnkStruct_0203eb40_2 *func_0203ef90(int a);
int func_0203ed8c(int);
int func_020961a8(int a);
int func_02095904(void);
void func_0203dfe4(int a);
void func_0203f32c(int a, unsigned char b);

int func_0203eb40(UnkStruct_0203eb40 *s)
{
    int k;

    k = func_0203f338();
    switch (k) {
        case 2:
            if (func_02073d90(data_020ccf94) != 0) {
                UnkStruct_0203eb40_2 *o = func_0203ef90(s->unk_10);
                if (func_0203ed8c((int) o) != 0 && s->unk_17 == 1) {
                    if (o->m(func_020961a8(4)) == 0) {
                        return 0;
                    }
                }
            }
            s->unk_16 = 2;
            break;
        case 1:
            s->unk_16 = 0;
            break;
        case 0:
            return 0;
    }
    if (s->unk_15 != 7) {
        if (func_02095904() == 0) {
            return 0;
        }
    }
    func_0203dfe4(s->unk_10);
    if (k == 1) {
        func_0203f32c(s->unk_10, s->unk_17);
    }
    return 1;
}
}
