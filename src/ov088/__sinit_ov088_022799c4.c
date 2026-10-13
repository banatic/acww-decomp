/* __sinit_ov088_022799c4 @ 0x022799c4, 0x184 bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char a, b, c, d;
} UnkStruct_022799c4;
typedef struct {
    int a;
    int b;
} UnkStruct_022799c4_2;
typedef struct {
    int x, y, z;
} UnkStruct_022799c4_3;
typedef struct {
    UnkStruct_022799c4_2 v;
    int pad_08;
} A12;

extern UnkStruct_022799c4 data_ov088_02279df4, data_ov088_02279de8, data_ov088_02279de4, data_ov088_02279de0,
    data_ov088_02279df0, data_ov088_02279dec;
extern A12 data_ov088_02279c14[5];
extern UnkStruct_022799c4_2 data_0213dd98;
extern UnkStruct_022799c4_2 data_ov088_02279b78, data_ov088_02279bb0, data_ov088_02279b88, data_ov088_02279b98;
extern UnkStruct_022799c4_2 data_ov088_02279e28[10];
extern UnkStruct_022799c4_2 data_ov088_02279ba8, data_ov088_02279bb8, data_ov088_02279b80, data_ov088_02279b60,
    data_ov088_02279b68, data_ov088_02279b70, data_ov088_02279bc0, data_ov088_02279b90, data_ov088_02279ba0;
extern UnkStruct_022799c4_3 data_ov088_02279e10[2];
extern void func_020012dc(void *);
extern int data_ov088_02279df8, data_ov088_02279e04;
extern void __register_global_object(void *o, void (*d)(void *), void *n);

void __sinit_ov088_022799c4(void)
{
    UnkStruct_022799c4_3 *p;
    data_ov088_02279df4.a = 0x1f;
    data_ov088_02279df4.b = 0x14;
    data_ov088_02279df4.c = 0x14;
    data_ov088_02279df4.d = 0x1f;
    data_ov088_02279de8.a = 0x14;
    data_ov088_02279de8.b = 0x14;
    data_ov088_02279de8.c = 0x1f;
    data_ov088_02279de8.d = 0x1f;
    data_ov088_02279de4.a = 0x1f;
    data_ov088_02279de4.b = 0x1f;
    data_ov088_02279de4.c = 0x14;
    data_ov088_02279de4.d = 0x1f;
    data_ov088_02279de0.a = 0x14;
    data_ov088_02279de0.b = 0x1f;
    data_ov088_02279de0.c = 0x14;
    data_ov088_02279de0.d = 0x1f;
    data_ov088_02279df0.a = 0x14;
    data_ov088_02279df0.b = 0x1f;
    data_ov088_02279df0.c = 0x1f;
    data_ov088_02279df0.d = 0x1f;
    data_ov088_02279dec.a = 0x14;
    data_ov088_02279dec.b = 0x18;
    data_ov088_02279dec.c = 0x18;
    data_ov088_02279dec.d = 0x1f;
    data_ov088_02279c14[0].v = data_0213dd98;
    data_ov088_02279c14[1].v = data_ov088_02279b78;
    data_ov088_02279c14[2].v = data_ov088_02279bb0;
    data_ov088_02279c14[3].v = data_ov088_02279b88;
    data_ov088_02279c14[4].v = data_ov088_02279b98;
    data_ov088_02279e28[0] = data_ov088_02279ba8;
    data_ov088_02279e28[1] = data_ov088_02279bb8;
    data_ov088_02279e28[2] = data_ov088_02279c14[0].v;
    data_ov088_02279e28[3] = data_ov088_02279b80;
    data_ov088_02279e28[4] = data_ov088_02279b60;
    data_ov088_02279e28[5] = data_ov088_02279b68;
    data_ov088_02279e28[6] = data_ov088_02279b70;
    data_ov088_02279e28[7] = data_ov088_02279bc0;
    data_ov088_02279e28[8] = data_ov088_02279b90;
    data_ov088_02279e28[9] = data_ov088_02279ba0;
    data_ov088_02279e10[0].x = 0x800;
    data_ov088_02279e10[0].y = 0;
    data_ov088_02279e10[0].z = 0x1000;
    __register_global_object(&data_ov088_02279e10[0], func_020012dc, &data_ov088_02279df8);
    p = &data_ov088_02279e10[1];
    p->x = -0x800;
    p->y = 0;
    p->z = 0x1000;
    __register_global_object(p, func_020012dc, &data_ov088_02279e04);
}
