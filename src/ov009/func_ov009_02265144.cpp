/* func_ov009_02265144 @ 0x02265144, 0xf8 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov009_022658dc19func_ov009_02265144Ev
 */

#include "cpp/ov009/Obj_ov009_022658dc.h"
#include "types.h"

// The object as this update sees it: slots by index, fields the class header
// knows only as padding inside its member objects.
struct UnkStruct_02265144 {
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
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual int f6c(int a);
    virtual void v28();
    virtual int f74();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual int f9c();
    virtual int fa0();
    char pad_04[0x134 - 4];
    u8 unk_134;
    char pad_135[0x136 - 0x135];
    u16 unk_136;
    char pad_138[0x198 - 0x138];
    int unk_198;
    char pad_19C[0x1f4 - 0x19c];
    int unk_1F4;
    char pad_1F8[0x238 - 0x1f8];
    int unk_238;
};

extern "C" int func_0203efc4(void);
extern "C" void func_ov009_02262f54(int *p);
extern "C" u16 *func_ov009_02262fcc(UnkStruct_02265144 *self);
extern "C" int func_0204bcdc(u16 *p);
extern "C" int func_0204bc64(u16 *p);
extern "C" int func_020b312c(u16 a);
extern "C" void func_ov009_022630b4(UnkStruct_02265144 *self);
extern "C" int func_020b65c4(void);
extern "C" void func_ov009_022643f4(UnkStruct_02265144 *self);
extern "C" void func_020b3328(int *p, int a, int b, int c);
extern "C" void func_020b3340(int *p, int a);
extern "C" void func_ov009_02264718(UnkStruct_02265144 *self);

int Obj_ov009_022658dc::func_ov009_02265144()
{
    UnkStruct_02265144 *self = (UnkStruct_02265144 *) this;
    u16 *p;
    u16 tmp;
    int r;
    unsigned int ok;
    int v1;
    int v2;

    if (func_0203efc4() == 0) {
        return 0;
    }
    func_ov009_02262f54(&self->unk_238);
    p = func_ov009_02262fcc(self);
    if (func_0204bcdc(p) != 0) {
        tmp = 0x501d;
        r = func_0204bc64(p);
        ok = (r == func_0204bc64(&tmp)) ? 1 : 0;
    } else {
        ok = (*p == 0x501d) ? 1 : 0;
    }
    if (ok != 0) {
        int c = func_020b312c(self->unk_136);
        if (self->unk_134 != c) {
            self->f6c(c);
        }
    }
    func_ov009_022630b4(self);
    if (func_020b65c4() != 0x2c) {
        ((Obj_ov009_022658dc *) self)->func_ov009_022638d0();
    }
    self->f74();
    if (func_020b65c4() != 0x2c) {
        func_ov009_022643f4(self);
    }
    v1 = self->f9c();
    v2 = self->fa0();
    func_020b3328(&self->unk_1F4, v1, 1, v2);
    func_020b3340(&self->unk_1F4, self->unk_198);
    func_ov009_02264718(self);
    return 1;
}
