/* __sinit_ov075_02279724 @ 0x02279724, 0x174 bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char a, b, c, d;
} UnkStruct_02279724;
typedef struct {
    int a;
    int b;
} UnkStruct_02279724_2;
typedef struct {
    int x, y, z;
} UnkStruct_02279724_3;
typedef struct {
    UnkStruct_02279724_2 unk_00;
    int pad_08;
    UnkStruct_02279724_2 unk_0C;
} UnkStruct_02279724_4;

extern UnkStruct_02279724 data_ov075_02279acc, data_ov075_02279ad4, data_ov075_02279ad0, data_ov075_02279ac4,
    data_ov075_02279ac8, data_ov075_02279ac0;
extern UnkStruct_02279724_4 data_ov075_02279930;
extern UnkStruct_02279724_2 __ptmf_null;
extern UnkStruct_02279724_2 data_ov075_022798c0;
extern UnkStruct_02279724_2 data_ov075_02279b08[12];
extern UnkStruct_02279724_2 data_ov075_022798d8, data_ov075_022798e0, data_ov075_022798f0, data_ov075_022798f8,
    data_ov075_022798c8, data_ov075_022798a0, data_ov075_022798a8, data_ov075_022798b0, data_ov075_022798b8,
    data_ov075_022798d0, data_ov075_022798e8;
extern UnkStruct_02279724_3 data_ov075_02279af0[2];
extern void func_020012dc(void *);
extern int data_ov075_02279ad8;
extern int data_ov075_02279ae4;
extern void __register_global_object(void *o, void *destructor, void *n);

#define DisposeGlobal_func_020012dc ((void *) &func_020012dc)

void __sinit_ov075_02279724(void)
{
    UnkStruct_02279724_3 *p;

    data_ov075_02279acc.a = 0x1f;
    data_ov075_02279acc.b = 0x14;
    data_ov075_02279acc.c = 0x14;
    data_ov075_02279acc.d = 0x1f;
    data_ov075_02279ad4.a = 0x14;
    data_ov075_02279ad4.b = 0x14;
    data_ov075_02279ad4.c = 0x1f;
    data_ov075_02279ad4.d = 0x1f;
    data_ov075_02279ad0.a = 0x1f;
    data_ov075_02279ad0.b = 0x1f;
    data_ov075_02279ad0.c = 0x14;
    data_ov075_02279ad0.d = 0x1f;
    data_ov075_02279ac4.a = 0x14;
    data_ov075_02279ac4.b = 0x1f;
    data_ov075_02279ac4.c = 0x14;
    data_ov075_02279ac4.d = 0x1f;
    data_ov075_02279ac8.a = 0x14;
    data_ov075_02279ac8.b = 0x1f;
    data_ov075_02279ac8.c = 0x1f;
    data_ov075_02279ac8.d = 0x1f;
    data_ov075_02279ac0.a = 0x14;
    data_ov075_02279ac0.b = 0x18;
    data_ov075_02279ac0.c = 0x18;
    data_ov075_02279ac0.d = 0x1f;
    data_ov075_02279930.unk_00 = __ptmf_null;
    data_ov075_02279930.unk_0C = data_ov075_022798c0;
    data_ov075_02279b08[0] = data_ov075_022798d8;
    data_ov075_02279b08[1] = data_ov075_022798e0;
    data_ov075_02279b08[2] = data_ov075_022798f0;
    data_ov075_02279b08[3] = data_ov075_022798f8;
    data_ov075_02279b08[4] = data_ov075_022798c8;
    data_ov075_02279b08[5] = data_ov075_022798a0;
    data_ov075_02279b08[6] = data_ov075_02279930.unk_00;
    data_ov075_02279b08[7] = data_ov075_022798a8;
    data_ov075_02279b08[8] = data_ov075_022798b0;
    data_ov075_02279b08[9] = data_ov075_022798b8;
    data_ov075_02279b08[10] = data_ov075_022798d0;
    data_ov075_02279b08[11] = data_ov075_022798e8;
    data_ov075_02279af0[0].x = 0x800;
    data_ov075_02279af0[0].y = 0;
    data_ov075_02279af0[0].z = 0x1000;
    __register_global_object(&data_ov075_02279af0[0], DisposeGlobal_func_020012dc, &data_ov075_02279ad8);
    p = &data_ov075_02279af0[1];
    p->x = -0x800;
    p->y = 0;
    p->z = 0x1000;
    __register_global_object(p, DisposeGlobal_func_020012dc, &data_ov075_02279ae4);
}

#undef DisposeGlobal_func_020012dc
