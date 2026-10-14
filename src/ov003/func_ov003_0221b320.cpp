/* func_ov003_0221b320 @ 0x0221b320, 0xf4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov003_022382ac19func_ov003_0221b320Ev
 */

#include "cpp/ov003/Obj_ov003_022382ac.h"
#include "types.h"

typedef struct {
    u32 x, y, z;
} Vec3u32;

// mwcc copies this one with a block move, as the ROM does; a C++ copy of
// Vec3u32 goes word by word.
typedef struct {
    u32 v[3];
} Vec3Words;

typedef struct {
    u16 b0 : 1;
    u16 b1 : 1;
    u16 b2 : 1;
    u16 b3 : 1;
    u16 b4 : 1;
    u16 b5 : 1;
    u16 b6 : 1;
    u16 b7 : 1;
    u16 b8 : 1;
    u16 b9 : 1;
    u16 b10 : 1;
    u16 b11 : 1;
    u16 b12 : 1;
    u16 b13 : 1;
    u16 b14 : 1;
    u16 b15 : 1;
} HalfFlags;

// The fields this update touches; the class header knows most of them only as
// padding inside its member objects.
typedef struct {
    u8 pad_00[0x5c];
    Vec3u32 vec1; // 0x5c
    Vec3u32 vec2; // 0x68
    u8 pad_74[0x2e8 - 0x74];
    u8 byte_at_2e8; // 0x2e8
    u8 pad_2E9[0x31c - 0x2e9];
    Vec3u32 vec3; // 0x31c
    Vec3u32 vec4; // 0x328
    u8 pad_334[0x374 - 0x334];
    u32 word_at_374; // 0x374
    HalfFlags flags; // 0x378
} UnkStruct_0221b320;

extern "C" {
u32 FX_Div(u32 a, u32 b);
void func_ov003_0221af94(UnkStruct_0221b320 *self);
void func_ov003_0221ac70(UnkStruct_0221b320 *self);
void func_020044d0(void *dst, const void *src);
}

unsigned int Obj_ov003_022382ac::func_ov003_0221b320()
{
    UnkStruct_0221b320 *self = (UnkStruct_0221b320 *) this;
    u32 ret;
    Vec3Words temp;
    Vec3u32 *p;

    ret = FX_Div(0xa000, 0x64000);
    if (!self->flags.b6) {
        self->word_at_374 = ret;
    }

    self->vec2.x = self->vec3.x;
    self->vec2.y = self->vec3.y;
    self->vec2.z = self->vec3.z;

    func_ov003_0221af94(self);
    ((Obj_ov003_022382ac *) self)->func_ov003_0221a244();
    ((Obj_ov003_022382ac *) self)->func_ov003_02219f88();
    func_ov003_0221ac70(self);

    self->flags.b7 = self->flags.b6;
    self->flags.b6 = 0;
    self->flags.b9 = 0;
    self->flags.b10 = 0;

    self->byte_at_2e8 = 0;

    self->vec2.x = self->vec1.x;
    self->vec2.y = self->vec1.y;
    self->vec2.z = self->vec1.z;

    p = &self->vec2;
    self->vec3.x = self->vec2.x;
    self->vec3.y = p->y;
    self->vec3.z = p->z;

    temp = *(Vec3Words *) &self->vec1;
    func_020044d0(&self->vec4, &temp);

    return 1;
}
