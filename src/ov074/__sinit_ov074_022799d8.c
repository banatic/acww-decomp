/* __sinit_ov074_022799d8 @ 0x022799d8, 0x144 bytes, Thumb, module ov074
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char a, b, c, d;
} UnkStruct_022799d8;
typedef struct {
    int a;
    int b;
} UnkStruct_022799d8_2;
typedef struct {
    int x, y, z;
} UnkStruct_022799d8_3;

extern UnkStruct_022799d8 data_ov074_02279d44, data_ov074_02279d54, data_ov074_02279d40, data_ov074_02279d58,
    data_ov074_02279d48, data_ov074_02279d50;
extern UnkStruct_022799d8_2 data_ov074_02279d9c[10];
extern UnkStruct_022799d8_2 data_ov074_02279b98, data_ov074_02279b58;
extern UnkStruct_022799d8_2 __ptmf_null;
extern UnkStruct_022799d8_2 data_ov074_02279b60, data_ov074_02279b68, data_ov074_02279b70, data_ov074_02279b78,
    data_ov074_02279b80, data_ov074_02279b88, data_ov074_02279b48;
extern UnkStruct_022799d8_3 data_ov074_02279d84[2];
extern void func_020012dc(void *);
extern int data_ov074_02279d5c;
extern int data_ov074_02279d68;
extern void __register_global_object(void *object, void *destructor, void *node);

#define DestroyGlobal_020012dc ((void *) &func_020012dc)

void __sinit_ov074_022799d8(void)
{
    UnkStruct_022799d8_3 *p;

    data_ov074_02279d44.a = 0x1f;
    data_ov074_02279d44.b = 0x14;
    data_ov074_02279d44.c = 0x14;
    data_ov074_02279d44.d = 0x1f;
    data_ov074_02279d54.a = 0x14;
    data_ov074_02279d54.b = 0x14;
    data_ov074_02279d54.c = 0x1f;
    data_ov074_02279d54.d = 0x1f;
    data_ov074_02279d40.a = 0x1f;
    data_ov074_02279d40.b = 0x1f;
    data_ov074_02279d40.c = 0x14;
    data_ov074_02279d40.d = 0x1f;
    data_ov074_02279d58.a = 0x14;
    data_ov074_02279d58.b = 0x1f;
    data_ov074_02279d58.c = 0x14;
    data_ov074_02279d58.d = 0x1f;
    data_ov074_02279d48.a = 0x14;
    data_ov074_02279d48.b = 0x1f;
    data_ov074_02279d48.c = 0x1f;
    data_ov074_02279d48.d = 0x1f;
    data_ov074_02279d50.a = 0x14;
    data_ov074_02279d50.b = 0x18;
    data_ov074_02279d50.c = 0x18;
    data_ov074_02279d50.d = 0x1f;
    data_ov074_02279d9c[0] = data_ov074_02279b98;
    data_ov074_02279d9c[1] = data_ov074_02279b58;
    data_ov074_02279d9c[2] = __ptmf_null;
    data_ov074_02279d9c[3] = data_ov074_02279b60;
    data_ov074_02279d9c[4] = data_ov074_02279b68;
    data_ov074_02279d9c[5] = data_ov074_02279b70;
    data_ov074_02279d9c[6] = data_ov074_02279b78;
    data_ov074_02279d9c[7] = data_ov074_02279b80;
    data_ov074_02279d9c[8] = data_ov074_02279b88;
    data_ov074_02279d9c[9] = data_ov074_02279b48;
    data_ov074_02279d84[0].x = 0x800;
    data_ov074_02279d84[0].y = 0;
    data_ov074_02279d84[0].z = 0x1000;
    __register_global_object(&data_ov074_02279d84[0], DestroyGlobal_020012dc, &data_ov074_02279d5c);
    p = &data_ov074_02279d84[1];
    p->x = -0x800;
    p->y = 0;
    p->z = 0x1000;
    __register_global_object(p, DestroyGlobal_020012dc, &data_ov074_02279d68);
}

#undef DestroyGlobal_020012dc
