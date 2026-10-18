/* __sinit_ov078_022798ac @ 0x022798ac, 0x144 bytes, Thumb, module ov078
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char a, b, c, d;
} UnkStruct_022798ac;
typedef struct {
    int a;
    int b;
} UnkStruct_022798ac_2;
typedef struct {
    int x, y, z;
} UnkStruct_022798ac_3;

extern UnkStruct_022798ac data_ov078_02279c04, data_ov078_02279c10, data_ov078_02279c14, data_ov078_02279c08,
    data_ov078_02279c0c, data_ov078_02279c00;
extern UnkStruct_022798ac_2 data_ov078_02279c48[10];
extern UnkStruct_022798ac_2 data_ov078_02279a38, data_ov078_02279a40;
extern UnkStruct_022798ac_2 __ptmf_null;
extern UnkStruct_022798ac_2 data_ov078_02279a20, data_ov078_02279a00, data_ov078_02279a08, data_ov078_02279a10,
    data_ov078_02279a18, data_ov078_02279a28, data_ov078_02279a30;
extern UnkStruct_022798ac_3 data_ov078_02279c30[2];
extern void func_020012dc(void *);
extern int data_ov078_02279c18;
extern int data_ov078_02279c24;
extern void __register_global_object(void *o, void *destructor, void *n);

#define DisposeGlobal_func_020012dc ((void *) &func_020012dc)

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_ov078_022798ac(void)
{
    UnkStruct_022798ac_3 *p;

    data_ov078_02279c04.a = 0x1f;
    data_ov078_02279c04.b = 0x14;
    data_ov078_02279c04.c = 0x14;
    data_ov078_02279c04.d = 0x1f;
    data_ov078_02279c10.a = 0x14;
    data_ov078_02279c10.b = 0x14;
    data_ov078_02279c10.c = 0x1f;
    data_ov078_02279c10.d = 0x1f;
    data_ov078_02279c14.a = 0x1f;
    data_ov078_02279c14.b = 0x1f;
    data_ov078_02279c14.c = 0x14;
    data_ov078_02279c14.d = 0x1f;
    data_ov078_02279c08.a = 0x14;
    data_ov078_02279c08.b = 0x1f;
    data_ov078_02279c08.c = 0x14;
    data_ov078_02279c08.d = 0x1f;
    data_ov078_02279c0c.a = 0x14;
    data_ov078_02279c0c.b = 0x1f;
    data_ov078_02279c0c.c = 0x1f;
    data_ov078_02279c0c.d = 0x1f;
    data_ov078_02279c00.a = 0x14;
    data_ov078_02279c00.b = 0x18;
    data_ov078_02279c00.c = 0x18;
    data_ov078_02279c00.d = 0x1f;
    data_ov078_02279c48[0] = data_ov078_02279a38;
    data_ov078_02279c48[1] = data_ov078_02279a40;
    data_ov078_02279c48[2] = __ptmf_null;
    data_ov078_02279c48[3] = data_ov078_02279a20;
    data_ov078_02279c48[4] = data_ov078_02279a00;
    data_ov078_02279c48[5] = data_ov078_02279a08;
    data_ov078_02279c48[6] = data_ov078_02279a10;
    data_ov078_02279c48[7] = data_ov078_02279a18;
    data_ov078_02279c48[8] = data_ov078_02279a28;
    data_ov078_02279c48[9] = data_ov078_02279a30;
    data_ov078_02279c30[0].x = 0x800;
    data_ov078_02279c30[0].y = 0;
    data_ov078_02279c30[0].z = 0x1000;
    __register_global_object(&data_ov078_02279c30[0], DisposeGlobal_func_020012dc, &data_ov078_02279c18);
    p = &data_ov078_02279c30[1];
    p->x = -0x800;
    p->y = 0;
    p->z = 0x1000;
    __register_global_object(p, DisposeGlobal_func_020012dc, &data_ov078_02279c24);
}

#undef DisposeGlobal_func_020012dc

#pragma section INIT end
