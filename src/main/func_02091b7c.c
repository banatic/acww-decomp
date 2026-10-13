/* func_02091b7c @ 0x02091b7c, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02091b7c {
    int x;
    int y;
    int z;
} UnkStruct_02091b7c;
typedef struct UnkStruct_02091b7c_2 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
} UnkStruct_02091b7c_2;
typedef struct Mid {
    UnkStruct_02091b7c_2 *p;
} Mid;
typedef struct UnkStruct_02091b7c_3 {
    char pad_00[0x18];
    Mid *m;
    int unk_1C;
    int unk_20;
    int unk_24;
    int unk_28;
} UnkStruct_02091b7c_3;

extern UnkStruct_02091b7c data_021d5658;
extern void func_02090db0(UnkStruct_02091b7c_3 *);

void func_02091b7c(UnkStruct_02091b7c_3 *self)
{
    UnkStruct_02091b7c v;
    int *g = (int *) &data_021d5658;

    v.x = g[0];
    v.y = g[1];
    v.z = g[2];
    v.y = 0;
    self->unk_20 = v.x + self->m->p->unk_04;
    self->unk_24 = *(volatile int *) &v.y + self->m->p->unk_08;
    self->unk_28 = v.z + self->m->p->unk_0C;
    func_02090db0(self);
}
