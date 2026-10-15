/* __sinit_ov079_02279e74 @ 0x02279e74, 0x144 bytes, Thumb, module ov079
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char a, b, c, d;
} UnkStruct_02279e74;
typedef struct {
    int a;
    int b;
} UnkStruct_02279e74_2;
typedef struct {
    int x, y, z;
} UnkStruct_02279e74_3;

extern UnkStruct_02279e74 data_ov079_0227a1c0, data_ov079_0227a1cc, data_ov079_0227a1d4, data_ov079_0227a1d8,
    data_ov079_0227a1c8, data_ov079_0227a1d0;
extern UnkStruct_02279e74_2 data_ov079_0227a224[10];
extern UnkStruct_02279e74_2 data_ov079_0227a010, data_ov079_02279fe8;
extern UnkStruct_02279e74_2 __ptmf_null;
extern UnkStruct_02279e74_2 data_ov079_02279ff0, data_ov079_02279ff8, data_ov079_0227a000, data_ov079_0227a008,
    data_ov079_0227a018, data_ov079_02279fd8, data_ov079_02279fd0;
extern UnkStruct_02279e74_3 data_ov079_0227a1f4[2];
extern void func_020012dc(void *);
extern int data_ov079_0227a1dc;
extern int data_ov079_0227a1e8;
extern void __register_global_object(void *object, void *destructor, void *node);

#define DestroyGlobal_020012dc ((void *) &func_020012dc)

void __sinit_ov079_02279e74(void)
{
    UnkStruct_02279e74_3 *p;

    data_ov079_0227a1c0.a = 0x1f;
    data_ov079_0227a1c0.b = 0x14;
    data_ov079_0227a1c0.c = 0x14;
    data_ov079_0227a1c0.d = 0x1f;
    data_ov079_0227a1cc.a = 0x14;
    data_ov079_0227a1cc.b = 0x14;
    data_ov079_0227a1cc.c = 0x1f;
    data_ov079_0227a1cc.d = 0x1f;
    data_ov079_0227a1d4.a = 0x1f;
    data_ov079_0227a1d4.b = 0x1f;
    data_ov079_0227a1d4.c = 0x14;
    data_ov079_0227a1d4.d = 0x1f;
    data_ov079_0227a1d8.a = 0x14;
    data_ov079_0227a1d8.b = 0x1f;
    data_ov079_0227a1d8.c = 0x14;
    data_ov079_0227a1d8.d = 0x1f;
    data_ov079_0227a1c8.a = 0x14;
    data_ov079_0227a1c8.b = 0x1f;
    data_ov079_0227a1c8.c = 0x1f;
    data_ov079_0227a1c8.d = 0x1f;
    data_ov079_0227a1d0.a = 0x14;
    data_ov079_0227a1d0.b = 0x18;
    data_ov079_0227a1d0.c = 0x18;
    data_ov079_0227a1d0.d = 0x1f;
    data_ov079_0227a224[0] = data_ov079_0227a010;
    data_ov079_0227a224[1] = data_ov079_02279fe8;
    data_ov079_0227a224[2] = __ptmf_null;
    data_ov079_0227a224[3] = data_ov079_02279ff0;
    data_ov079_0227a224[4] = data_ov079_02279ff8;
    data_ov079_0227a224[5] = data_ov079_0227a000;
    data_ov079_0227a224[6] = data_ov079_0227a008;
    data_ov079_0227a224[7] = data_ov079_0227a018;
    data_ov079_0227a224[8] = data_ov079_02279fd8;
    data_ov079_0227a224[9] = data_ov079_02279fd0;
    data_ov079_0227a1f4[0].x = 0x800;
    data_ov079_0227a1f4[0].y = 0;
    data_ov079_0227a1f4[0].z = 0x1000;
    __register_global_object(&data_ov079_0227a1f4[0], DestroyGlobal_020012dc, &data_ov079_0227a1dc);
    p = &data_ov079_0227a1f4[1];
    p->x = -0x800;
    p->y = 0;
    p->z = 0x1000;
    __register_global_object(p, DestroyGlobal_020012dc, &data_ov079_0227a1e8);
}

#undef DestroyGlobal_020012dc
