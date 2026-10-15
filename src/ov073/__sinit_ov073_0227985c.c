/* __sinit_ov073_0227985c @ 0x0227985c, 0x144 bytes, Thumb, module ov073
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char a, b, c, d;
} UnkStruct_0227985c;
typedef struct {
    int a;
    int b;
} UnkStruct_0227985c_2;
typedef struct {
    int x, y, z;
} UnkStruct_0227985c_3;

extern UnkStruct_0227985c data_ov073_02279bc4, data_ov073_02279bd8, data_ov073_02279bcc, data_ov073_02279bd4,
    data_ov073_02279bc0, data_ov073_02279bc8;
extern UnkStruct_0227985c_2 data_ov073_02279c14[10];
extern UnkStruct_0227985c_2 data_ov073_022799c8, data_ov073_022799e0;
extern UnkStruct_0227985c_2 __ptmf_null;
extern UnkStruct_0227985c_2 data_ov073_022799e8, data_ov073_022799f0, data_ov073_022799f8, data_ov073_02279a00,
    data_ov073_02279a08, data_ov073_022799d8, data_ov073_022799d0;
extern UnkStruct_0227985c_3 data_ov073_02279bfc[2];
extern void func_020012dc(void *);
extern int data_ov073_02279be4;
extern int data_ov073_02279bf0;
extern void __register_global_object(void *object, void *destructor, void *node);

#define DestroyGlobal_020012dc ((void *) &func_020012dc)

void __sinit_ov073_0227985c(void)
{
    UnkStruct_0227985c_3 *p;

    data_ov073_02279bc4.a = 0x1f;
    data_ov073_02279bc4.b = 0x14;
    data_ov073_02279bc4.c = 0x14;
    data_ov073_02279bc4.d = 0x1f;
    data_ov073_02279bd8.a = 0x14;
    data_ov073_02279bd8.b = 0x14;
    data_ov073_02279bd8.c = 0x1f;
    data_ov073_02279bd8.d = 0x1f;
    data_ov073_02279bcc.a = 0x1f;
    data_ov073_02279bcc.b = 0x1f;
    data_ov073_02279bcc.c = 0x14;
    data_ov073_02279bcc.d = 0x1f;
    data_ov073_02279bd4.a = 0x14;
    data_ov073_02279bd4.b = 0x1f;
    data_ov073_02279bd4.c = 0x14;
    data_ov073_02279bd4.d = 0x1f;
    data_ov073_02279bc0.a = 0x14;
    data_ov073_02279bc0.b = 0x1f;
    data_ov073_02279bc0.c = 0x1f;
    data_ov073_02279bc0.d = 0x1f;
    data_ov073_02279bc8.a = 0x14;
    data_ov073_02279bc8.b = 0x18;
    data_ov073_02279bc8.c = 0x18;
    data_ov073_02279bc8.d = 0x1f;
    data_ov073_02279c14[0] = data_ov073_022799c8;
    data_ov073_02279c14[1] = data_ov073_022799e0;
    data_ov073_02279c14[2] = __ptmf_null;
    data_ov073_02279c14[3] = data_ov073_022799e8;
    data_ov073_02279c14[4] = data_ov073_022799f0;
    data_ov073_02279c14[5] = data_ov073_022799f8;
    data_ov073_02279c14[6] = data_ov073_02279a00;
    data_ov073_02279c14[7] = data_ov073_02279a08;
    data_ov073_02279c14[8] = data_ov073_022799d8;
    data_ov073_02279c14[9] = data_ov073_022799d0;
    data_ov073_02279bfc[0].x = 0x800;
    data_ov073_02279bfc[0].y = 0;
    data_ov073_02279bfc[0].z = 0x1000;
    __register_global_object(&data_ov073_02279bfc[0], DestroyGlobal_020012dc, &data_ov073_02279be4);
    p = &data_ov073_02279bfc[1];
    p->x = -0x800;
    p->y = 0;
    p->z = 0x1000;
    __register_global_object(p, DestroyGlobal_020012dc, &data_ov073_02279bf0);
}

#undef DestroyGlobal_020012dc
