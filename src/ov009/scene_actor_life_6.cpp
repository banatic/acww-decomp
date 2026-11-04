/* scene_actor_life_6: 2 functions, module ov009
 * mwccarm 1.2/base -O4,s
 * func_ov009_022650d0 @ 0x022650d0, 0x74 bytes, Thumb
 * func_ov009_02265024 @ 0x02265024, 0xac bytes, Thumb
 */

#include "types.h"

struct Vec {
    int a;
    int b;
};

struct UnkStruct_022650d0 {
    u8 pad[4];
};

class UnkStruct_022650d0_2 {
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
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual Vec v45();
    u8 pad[0x235 - 4];
    u8 flags;
    u8 pad_236[2];
    UnkStruct_022650d0 sub;
};

extern "C" u16 *func_ov009_02262fcc(UnkStruct_022650d0_2 *self);
extern "C" void func_ov009_02262f2c(UnkStruct_022650d0 *dst, const Vec *v, u16 x);
extern "C" void func_02003420(UnkStruct_022650d0_2 *self, void *p);

struct UnkStruct_02265024 {
    virtual int v0();
    virtual int v1();
    virtual int v2();
    virtual int v3();
    virtual int v4();
    virtual int v5();
    virtual int v6();
    virtual int v7();
    virtual int v8();
    virtual int v9();
    virtual int v10();
    virtual int v11();
    virtual int v12();
    virtual int v13();
    virtual int v14();
    virtual int v15();
    virtual int v16();
    virtual int v17();
    virtual int v18();
    virtual int v19();
    virtual int v20();
    virtual int v21();
    virtual int v22();
    virtual int v23();
    virtual int v24();
    virtual int v25();
    virtual int v26();
    virtual int v27();
    virtual int v28();
    virtual int v29();
    virtual int v30();
    virtual int v31();
    virtual int v32();
    virtual int v33();
    virtual int v34();
    virtual int v35();
    virtual int v36();
    virtual int v37();
    virtual int v38();
    virtual int v39();
    virtual int v40();
    virtual int v41();
    virtual int v42();
    virtual int v43();
    virtual int fb0();
    char pad_04[0x235 - 4];
    u8 unk_235;
    char pad_236[0x294 - 0x236];
    int unk_294;
    char pad_298[0x2a0 - 0x298];
    int unk_2A0;
    int unk_2A4;
};

extern "C" int func_020033ec(void *unused0);
extern "C" int func_0204bcdc(u16 *p);
extern "C" int func_0204bc64(u16 *p);
extern "C" int func_0203adc4(int *a, int b, int c);
extern "C" void func_ov009_022632c8(UnkStruct_02265024 *self);

extern "C" void func_ov009_022650d0(UnkStruct_022650d0_2 *self, void *arg)
{
    const Vec &v = self->v45();
    func_ov009_02262f2c(&self->sub, &v, *func_ov009_02262fcc(self));
    if (self->flags & 2) {
        self->flags |= 8;
    } else {
        self->flags &= ~8;
    }
    self->flags &= ~2;
    self->flags &= ~4;
    func_02003420(self, arg);
}

extern "C" int func_ov009_02265024(UnkStruct_02265024 *self)
{
    u16 *p;
    u16 tmp;
    int r;
    unsigned int ok;
    if (func_020033ec(self) == 0) {
        return 0;
    }
    if ((self->unk_235 & 1) == 0) {
        p = func_ov009_02262fcc((UnkStruct_022650d0_2 *) self);
        if (func_0204bcdc(p) != 0) {
            tmp = 0x500b;
            r = func_0204bc64(p);
            ok = (r == func_0204bc64(&tmp)) ? 1 : 0;
        } else {
            ok = (*p == 0x500b) ? 1 : 0;
        }
        if (ok != 0 || func_0203adc4(&self->unk_294, self->unk_2A0, self->unk_2A4) == 0) {
            if (self->fb0() != 0) {
                func_ov009_022632c8(self);
            }
            return 1;
        }
    }
    return 0;
}
