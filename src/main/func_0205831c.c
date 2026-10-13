/* func_0205831c @ 0x0205831c, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Vec {
    int x;
    int y;
    int z;
} Vec;
typedef struct UnkStruct_0205831c {
    unsigned char pad_00[0x8e];
    short angle;
} UnkStruct_0205831c;

typedef struct UnkStruct_0205831c_2 {
    unsigned char pad_00[0x60];
    unsigned char mtx[0x78 - 0x60];
    Vec vec; // 0x78
    unsigned char pad_84[0xcc - 0x84];
    UnkStruct_0205831c *ent; // 0xcc
    unsigned char pad_D0[0xd6 - 0xd0];
    unsigned short count; // 0xd6
} UnkStruct_0205831c_2;

extern Vec data_021c9390;
extern void func_0205967c(UnkStruct_0205831c_2 *self, unsigned char *mtx);
extern void func_02059674(UnkStruct_0205831c_2 *self, int flag);
extern void func_020ea6e0(Vec *v, int angle);
extern void VEC_Add(unsigned char *mtx, Vec *v, unsigned char *out);

void func_0205831c(UnkStruct_0205831c_2 *self)
{
    if ((int) self->count >= 10) {
        return;
    }
    func_0205967c(self, self->mtx);
    if (self->ent != 0) {
        self->vec.x = data_021c9390.x;
        self->vec.y = data_021c9390.y;
        self->vec.z = data_021c9390.z;
        func_020ea6e0(&self->vec, self->ent->angle);
    }
    VEC_Add(self->mtx, &self->vec, self->mtx);
    self->count = self->count + 1;
    if ((int) self->count >= 10) {
        func_02059674(self, 0);
    }
}
