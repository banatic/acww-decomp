/* func_ov110_0229cb78 @ 0x0229cb78, 0x68 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov002_0220a05c(void *a, int b, int c, int d, int e);
extern "C" void func_ov002_02208098(void *a, int b);
extern "C" int func_ov110_0229cc14(void *obj);
extern "C" int func_ov110_0229cc04(void *obj);
extern "C" int func_ov110_0229c2c8(void *obj, int n);
extern "C" void func_ov110_0229c2a8(void *obj, int n);

class UnkStruct_0229cb78 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
};

struct MainObject {
    char pad_00[0x8d];
    unsigned char unk_8D;
    char pad_8E[0x6a];
    unsigned char unk_F8;
    char pad_F9[0x21e7];
    UnkStruct_0229cb78 subObj;
};

extern "C" void func_ov110_0229cb78(MainObject *obj)
{
    int v1 = func_ov110_0229cc14(obj);
    int v2 = func_ov110_0229cc04(obj);
    func_ov002_0220a05c(&obj->subObj, v1, v2, 3, 1);
    obj->unk_F8 = obj->unk_8D;
    func_ov002_02208098(obj, 8);
    if (func_ov110_0229c2c8(obj, 0x100) != 0) {
        obj->subObj.f3();
        func_ov110_0229c2a8(obj, 0x100);
    }
}
