/* func_020925d0 @ 0x020925d0, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char b[4];
} Key;
typedef struct {
    int x;
    int y;
    int z;
} Vec;
typedef struct {
    int pad_00;
    int unk_04;
    int unk_08;
    int unk_0C;
} UnkStruct_020925d0;
typedef struct {
    UnkStruct_020925d0 *p;
} Mid;
typedef struct {
    char pad_00[0x18];
    Mid *unk_18;
    int pad_1C;
    int unk_20;
    int unk_24;
    int unk_28;
} UnkStruct_020925d0_2;
typedef struct {
    char pad_00[4];
    Key key;
    char pad_08[4];
    UnkStruct_020925d0_2 *unk_0C;
} UnkStruct_020925d0_3;
typedef struct {
    char pad_00[0x1c];
} UnkStruct_020925d0_4;

extern Vec data_021d5658;
extern UnkStruct_020925d0_4 data_021d52d8[];
extern void func_02090db0(UnkStruct_020925d0_2 *s);
extern void MI_CpuCopy8(void *dst, const void *src, unsigned int size);

void func_020925d0(UnkStruct_020925d0_3 *o)
{
    struct {
        Key k;
        Vec v;
    } L;
    UnkStruct_020925d0_2 *s;
    Vec *g;

    g = (Vec *) &data_021d5658;
    L.k = o->key;
    L.v.x = g->x;
    L.v.y = g->y;
    L.v.z = g->z;
    s = o->unk_0C;
    s->unk_20 = L.v.x + s->unk_18->p->unk_04;
    s->unk_24 = L.v.y + s->unk_18->p->unk_08;
    s->unk_28 = L.v.z + s->unk_18->p->unk_0C;
    func_02090db0(o->unk_0C);
    MI_CpuCopy8(g, &data_021d52d8[*(unsigned char *) &L], 0x1c);
}
