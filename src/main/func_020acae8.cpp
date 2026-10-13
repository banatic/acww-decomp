/* func_020acae8 @ 0x020acae8, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020acae8_2 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
};

typedef struct {
    char pad_00[0x10];
    UnkStruct_020acae8_2 obj;
} ParamType;

typedef struct {
    int unk_00;
} UnkStruct_020acae8;

extern "C" int func_0208e958(UnkStruct_020acae8_2 *p);
extern "C" int func_0208aeec(ParamType *p);
extern "C" int func_0208aef0(ParamType *p);
extern "C" void func_02088df8(int, int, int, int, int, int, int, int, int, int, int, int);
extern UnkStruct_020acae8 *data_020d5b3c;

extern "C" void func_020acae8(ParamType *param)
{
    if (func_0208e958(&param->obj) == 0) {
        return;
    }
    param->obj.f2();
    int g = data_020d5b3c->unk_00;
    int a = func_0208aeec(param);
    int b = func_0208aef0(param);
    func_02088df8(0, g, b, a, -1, 0, 0x1000, 0x1000, 0, -1, 0, 0);
}
