/* func_02032788 @ 0x02032788, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Vec3 {
    int x, y, z;
} Vec3;

typedef struct Elem {
    int unk_00;
    int unk_04;
    int unk_08;
    char pad0[8];
    unsigned char unk_14;
    char pad1[0xf];
} Elem;

typedef struct UnkStruct_02032788 {
    char pad0[4];
    Vec3 *unk_04;
    Vec3 unk_08;
    char pad1[4];
    unsigned char unk_18;
    char pad_19[3];
    void *unk_1C;
    char pad_20[4];
    int unk_24;
    int unk_28;
    int unk_2C;
    int unk_30;
    char pad_34[8];
    int unk_3C;
} UnkStruct_02032788;

extern Vec3 data_021c317c;

extern int func_020304d4(Elem *e, Vec3 *b, Vec3 *c);
extern int func_02030324(Elem *e, Vec3 *b, Vec3 *c);
extern void func_02034280(void *dst, void *src);
extern int func_020ea838(Vec3 *v);

static __inline void VEC_Set(volatile Vec3 *p, int x, int y, int z)
{
    p->x = x;
    p->y = y;
    p->z = z;
}

void func_02032788(UnkStruct_02032788 *self, void *arg)
{
    volatile Vec3 tmp;
    Elem *base;
    Elem *p;

    self->unk_3C = *(int *) arg;
    base = (Elem *) ((char *) arg + 4);
    for (p = base; p < base + self->unk_3C; p++) {
        VEC_Set(&tmp, self->unk_04->x, self->unk_04->y, self->unk_04->z);
        if (func_020304d4(p, *(Vec3 *volatile *) &self->unk_04, &self->unk_08) != 0) {
            func_02034280(&self->unk_1C, &p->unk_14);
            self->unk_24 = data_021c317c.x;
            self->unk_28 = data_021c317c.y;
            self->unk_2C = data_021c317c.z;
            self->unk_30 = p->unk_14;
            self->unk_18 = 1;
        }
        VEC_Set(&tmp, self->unk_04->x, self->unk_04->y, self->unk_04->z);
        if (func_02030324(p, *(Vec3 *volatile *) &self->unk_04, &self->unk_08) != 0) {
            func_02034280(&self->unk_1C, &p->unk_14);
            VEC_Set((Vec3 *) &self->unk_24, self->unk_04->x - p->unk_00, 0, self->unk_04->z - p->unk_08);
            func_020ea838((Vec3 *) &self->unk_24);
            self->unk_30 = p->unk_14;
            self->unk_18 = 1;
        }
    }
}
