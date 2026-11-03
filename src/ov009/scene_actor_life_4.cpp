/* scene_actor_life_4: 2 functions, module ov009
 * mwccarm 1.2/base -O4,s
 * func_ov009_0226523c @ 0x0226523c, 0x15c bytes, Thumb, emits _ZN18Obj_ov009_022658dc19func_ov009_0226523cEv
 * func_ov009_02265144 @ 0x02265144, 0xf8 bytes, Thumb, emits _ZN18Obj_ov009_022658dc19func_ov009_02265144Ev
 */

#include "cpp/ov009/Obj_ov009_022658dc.h"
#include "types.h"

// The object as this initialiser sees it: slots by index, fields the class
// header knows only as padding inside its member objects.
struct UnkStruct_0226523c {
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
    u32 unk_04;              // 0x04
    u32 unk_08;              // 0x08
    u8 pad_0C[0x5c - 0x0c];  // 0x0c..0x5b
    int unk_5C;              // 0x5c
    u8 pad_60[0x64 - 0x60];  // 0x60..0x63
    int unk_64;              // 0x64
    u8 pad_68[0x136 - 0x68]; // 0x68..0x135
    u16 unk_136;             // 0x136
    // 2 bytes padding for alignment
    u32 unk_138;               // 0x138
    u32 unk_13C;               // 0x13c
    u8 pad_140[0x1f4 - 0x140]; // 0x140..0x1f3
    u32 unk_1F4;               // 0x1f4
    u8 pad_1F8[0x22c - 0x1f8]; // 0x1f8..0x22b
    u32 unk_22C;               // 0x22c
    u32 unk_230;               // 0x230
    u8 pad_234[0x2a8 - 0x234]; // 0x234..0x2a7
    u32 unk_2A8;               // 0x2a8
    u8 pad_2AC[0x2b0 - 0x2ac]; // 0x2ac..0x2af
    u32 unk_2B0;               // 0x2b0
};

typedef struct {
    u32 data[12]; // 48 bytes
} Buf48;

extern "C" int func_ov003_02220268(UnkStruct_0226523c *self);
extern "C" void func_0203efb0(UnkStruct_0226523c *self, u16 val);
extern "C" void func_02055dc8(void *dest, void (*callback)(void *), UnkStruct_0226523c *self);
extern "C" int func_0203f844(void *dest, void *src);
extern "C" void func_020e96c8(void *dest, u32 a, u32 b, u32 c);
extern "C" void func_020e9774(void *dest, int p1);
extern "C" void func_020b3380(void *dest, int p1, int p2);
extern "C" void func_0203edf4(UnkStruct_0226523c *self, int p1);
extern "C" int func_ov009_02264ad8(UnkStruct_0226523c *self, int a, int b, int c);
extern "C" void func_ov009_02264f68(UnkStruct_0226523c *self);
extern "C" void func_ov009_02264e98(UnkStruct_0226523c *self);
extern "C" void func_ov009_022646b8(UnkStruct_0226523c *self, void *p);
extern "C" void func_ov009_02264618(UnkStruct_0226523c *self, void *p);
extern "C" void func_ov009_02264444(UnkStruct_0226523c *self, void *p);
extern "C" void *func_ov009_02264884(UnkStruct_0226523c *self);
extern "C" int func_ov009_0226321c(UnkStruct_0226523c *self, void *p, int p2);
extern "C" void func_ov009_022655c4(void *state);

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

extern "C" int func_0203efc4(void *argument0);
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

int Obj_ov009_022658dc::func_ov009_0226523c()
{
    UnkStruct_0226523c *self = (UnkStruct_0226523c *) this;
    int r4, r6, r7;
    u16 val;
    void *p;
    int v2;
    Buf48 buffer0, buffer1, buffer3;
    u32 buffer2[4];

    func_ov003_02220268(self);

    self->unk_22C = self->unk_5C >> 13;
    self->unk_230 = self->unk_64 >> 13;

    val = (u16) (((self->unk_230 & 0xff) << 8) | (self->unk_22C & 0xff));
    func_0203efb0(self, val);

    self->unk_136 = (u16) self->unk_08;
    self->unk_138 = self->unk_136 & 0xfff;

    r4 = self->v41();
    r6 = self->v42();
    r7 = self->v43();

    func_ov009_02264ad8(self, r4, r6, r7);

    func_ov009_02264f68(self);
    func_ov009_02264e98(self);
    func_ov009_022646b8(self, &buffer0);

    func_02055dc8(&self->unk_13C, func_ov009_022655c4, self);

    buffer1 = buffer0;

    func_ov009_02264618(self, &buffer1);

    r4 = func_0203f844(buffer2, (char *) self + 0x5c);
    func_020e96c8(&buffer3, buffer2[0], buffer2[1], buffer2[2]);
    func_020e9774(&buffer3, r4);
    func_ov009_02264444(self, &buffer3);

    p = func_ov009_02264884(self);
    if (p != 0) {
        v2 = *(int *) p;
    } else {
        v2 = 0;
    }
    func_020b3380(&self->unk_1F4, v2, 1);

    func_0203edf4(self, 0);

    if (func_ov009_0226321c(self, &self->unk_2A8, 0) != 0) {
        self->unk_2B0 -= 0x4000;
    }

    r4 = self->v28();
    ((Obj_ov009_022658dc *) self)->func_ov009_022639a0(0);

    return r4;
}

int Obj_ov009_022658dc::func_ov009_02265144()
{
    UnkStruct_02265144 *self = (UnkStruct_02265144 *) this;
    u16 *p;
    u16 tmp;
    int r;
    unsigned int ok;
    int v1;
    int v2;

    if (func_0203efc4((void *) this) == 0) {
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
