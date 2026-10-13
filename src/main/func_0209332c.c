/* func_0209332c @ 0x0209332c, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

struct Vec3 {
    int x;
    int y;
    int z;
};

extern short data_021d5658[];
extern short FX_SinCosTable_[];
extern void func_020ea6e0(struct Vec3 *, int, int);
extern void VEC_Add(struct Vec3 *, short *, struct Vec3 *);
extern void func_02090db0(void *);
extern void func_020933c0(void);

struct UnkStruct_0209332c_2 {
    char pad_00[4];
    int unk_04;
    int unk_08;
    int unk_0C;
};

struct UnkStruct_0209332c {
    struct UnkStruct_0209332c_2 *b;
};

struct MainObj {
    char pad_00[0x18];
    struct UnkStruct_0209332c *unk_18;
    char pad_1C[4];
    int unk_20;
    int unk_24;
    int unk_28;
    char pad_2C[0x10];
    short unk_3C;
    short unk_3E;
    short unk_40;
    char pad_42[0x36];
    void (*unk_78)(void);
};

void func_0209332c(struct MainObj *self, const struct Vec3 *src, int arg2)
{
    struct Vec3 tmp;
    int val, i;
    short *base = data_021d5658;

    val = (short) (base[6] + arg2);

    tmp.x = src->x;
    tmp.y = src->y;
    tmp.z = src->z;

    func_020ea6e0(&tmp, base[6], arg2);
    VEC_Add(&tmp, base, &tmp);

    i = ((unsigned short) val >> 4) << 1;

    self->unk_20 = tmp.x + self->unk_18->b->unk_04;
    self->unk_24 = tmp.y + self->unk_18->b->unk_08;
    self->unk_28 = tmp.z + self->unk_18->b->unk_0C;

    self->unk_3C = FX_SinCosTable_[i];
    self->unk_3E = 0;
    *(short *) ((char *) self + 0x40) = FX_SinCosTable_[i + 1];

    func_02090db0(self);
    self->unk_78 = func_020933c0;
}
