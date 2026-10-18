/* __sinit_020c4270 @ 0x020c4270, 0x810 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} UnkStruct_020c4270;
typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_020c4270_2;

extern void __register_global_object(void *, void *, void *);
extern void func_020012dc(void *);

extern UnkStruct_020c4270_2 data_021c16b4[2], data_021c16e4[2];
extern UnkStruct_020c4270_2 data_021c157c[4];

extern UnkStruct_020c4270 data_021c1794[6];
extern UnkStruct_020c4270 data_021c1ad4[16];
extern UnkStruct_020c4270 data_021c1b54[16];
extern UnkStruct_020c4270 data_021c1bd4[16];
extern UnkStruct_020c4270 data_021c1c54[16];
extern UnkStruct_020c4270 data_021c1cd4[2];
extern UnkStruct_020c4270 data_021c17c4[10];
extern UnkStruct_020c4270 data_021c1914[16];
extern UnkStruct_020c4270 data_021c1994[16];
extern UnkStruct_020c4270 data_021c1a14[16];
extern UnkStruct_020c4270 data_021c1a94[8];
extern UnkStruct_020c4270 data_021c172c, data_021c1734, data_021c173c, data_021c1744;

extern UnkStruct_020c4270 data_020d85cc, data_020d87fc, data_020d8b74, data_020d87bc, data_020d878c, data_020d879c;
extern UnkStruct_020c4270 data_020d86bc, data_020d8534, __ptmf_null, data_020d8544, data_020d855c, data_020d8564,
    data_020d8924, data_020d87c4, data_020d87cc, data_020d87d4, data_020d8b94, data_020d86d4;
extern UnkStruct_020c4270 data_020d8bc4, data_020d8bbc, data_020d8bb4, data_020d8bac, data_020d8ba4, data_020d8b9c,
    data_020d898c, data_020d8b8c, data_020d8b84, data_020d8b7c, data_020d89bc, data_020d8b6c;
extern UnkStruct_020c4270 data_020d8b64, data_020d89d4, data_020d89dc, data_020d8b4c, data_020d8b44, data_020d8b3c,
    data_020d8b34, data_020d8b2c, data_020d8a04, data_020d8b1c, data_020d8b14, data_020d8b0c, data_020d8b04, data_020d8afc;
extern UnkStruct_020c4270 data_020d8a2c, data_020d8aec, data_020d8a3c, data_020d8adc, data_020d8ad4, data_020d8acc,
    data_020d8ac4, data_020d8a9c, data_020d8aa4, data_020d8ab4, data_020d8abc, data_020d8ae4;
extern UnkStruct_020c4270 data_020d8af4;
extern UnkStruct_020c4270 data_020d86e4, data_020d86f4, data_020d86fc, data_020d8714, data_020d871c, data_020d872c,
    data_020d8734, data_020d8754, data_020d8824, data_020d876c;
extern UnkStruct_020c4270 data_020d86c4, data_020d86ac, data_020d86a4, data_020d8554, data_020d8684, data_020d857c,
    data_020d8664, data_020d8594, data_020d864c, data_020d85b4, data_020d894c, data_020d85c4, data_020d85d4, data_020d8614,
    data_020d85ec, data_020d8674;
extern UnkStruct_020c4270 data_020d86ec, data_020d8704, data_020d8724, data_020d873c, data_020d875c, data_020d877c,
    data_020d8794, data_020d87a4, data_020d87ec, data_020d88b4, data_020d8964, data_020d89a4, data_020d89b4, data_020d89fc,
    data_020d8a34, data_020d8aac;
extern UnkStruct_020c4270 data_020d8a7c, data_020d869c, data_020d856c, data_020d8584, data_020d85a4, data_020d8634,
    data_020d85e4, data_020d85fc, data_020d870c, data_020d8744, data_020d8784, data_020d8b5c, data_020d88cc, data_020d89ac,
    data_020d89c4, data_020d8b54;
extern UnkStruct_020c4270 data_020d853c, data_020d859c, data_020d85bc, data_020d867c, data_020d874c, data_020d87f4,
    data_020d880c, data_020d8a14;

#pragma define_section INIT ".init" RX
#pragma section INIT begin

void __sinit_020c4270(void)
{
    UnkStruct_020c4270 t;
    UnkStruct_020c4270_2 *p;

    p = &data_021c16b4[0];
    p->a = 0x800;
    p->b = 0;
    p->c = 0x1000;
    __register_global_object((void *) (p), (((void *) func_020012dc)), (void *) (&data_021c157c[0]));
    p = &data_021c16b4[1];
    p->a = -0x800;
    p->b = 0;
    p->c = 0x1000;
    __register_global_object((void *) (p), (((void *) func_020012dc)), (void *) (&data_021c157c[1]));
    p = &data_021c16e4[0];
    p->a = 0x700;
    p->b = 0;
    p->c = 0xf00;
    __register_global_object((void *) (p), (((void *) func_020012dc)), (void *) (&data_021c157c[2]));
    p = &data_021c16e4[1];
    p->a = -0x700;
    p->b = 0;
    p->c = 0xf00;
    __register_global_object((void *) (p), (((void *) func_020012dc)), (void *) (&data_021c157c[3]));

    data_021c1794[0] = data_020d85cc;
    data_021c1794[1] = data_020d87fc;
    data_021c1794[2] = data_020d8b74;
    data_021c1794[3] = data_020d87bc;
    data_021c1794[4] = data_020d878c;
    data_021c1794[5] = data_020d879c;

    data_021c1ad4[0] = data_020d86bc;
    data_021c1ad4[1] = data_020d8534;
    t = __ptmf_null;
    data_021c1ad4[2] = t;
    data_021c1ad4[3] = data_020d8544;
    data_021c1ad4[4] = data_020d855c;
    data_021c1ad4[5] = t;
    data_021c1ad4[6] = data_020d8564;
    data_021c1ad4[7] = data_020d8924;
    data_021c1ad4[8] = t;
    data_021c1ad4[9] = data_020d87c4;
    data_021c1ad4[10] = data_020d87cc;
    data_021c1ad4[11] = t;
    data_021c1ad4[12] = data_020d87d4;
    data_021c1ad4[13] = data_020d8b94;
    data_021c1ad4[14] = t;
    data_021c1ad4[15] = data_020d86d4;

    data_021c1b54[0] = data_020d8bc4;
    data_021c1b54[1] = t;
    data_021c1b54[2] = data_020d8bbc;
    data_021c1b54[3] = data_020d8bb4;
    data_021c1b54[4] = t;
    data_021c1b54[5] = data_020d8bac;
    data_021c1b54[6] = data_020d8ba4;
    data_021c1b54[7] = data_020d8b9c;
    data_021c1b54[8] = data_020d898c;
    data_021c1b54[9] = data_020d8b8c;
    data_021c1b54[10] = t;
    data_021c1b54[11] = data_020d8b84;
    data_021c1b54[12] = data_020d8b7c;
    data_021c1b54[13] = t;
    data_021c1b54[14] = data_020d89bc;
    data_021c1b54[15] = data_020d8b6c;

    data_021c1bd4[0] = data_020d8b64;
    data_021c1bd4[1] = data_020d89d4;
    data_021c1bd4[2] = data_020d89dc;
    data_021c1bd4[3] = data_020d8b4c;
    data_021c1bd4[4] = data_020d8b44;
    data_021c1bd4[5] = t;
    data_021c1bd4[6] = data_020d8b3c;
    data_021c1bd4[7] = data_020d8b34;
    data_021c1bd4[8] = data_020d8b2c;
    data_021c1bd4[9] = data_020d8a04;
    data_021c1bd4[10] = data_020d8b1c;
    data_021c1bd4[11] = data_020d8b14;
    data_021c1bd4[12] = data_020d8b0c;
    data_021c1bd4[13] = data_020d8b04;
    data_021c1bd4[14] = t;
    data_021c1bd4[15] = data_020d8afc;

    data_021c1c54[0] = data_020d8a2c;
    data_021c1c54[1] = t;
    data_021c1c54[2] = data_020d8aec;
    data_021c1c54[3] = data_020d8a3c;
    data_021c1c54[4] = data_020d8adc;
    data_021c1c54[5] = t;
    data_021c1c54[6] = data_020d8ad4;
    data_021c1c54[7] = data_020d8acc;
    data_021c1c54[8] = t;
    data_021c1c54[9] = data_020d8ac4;
    data_021c1c54[10] = data_020d8a9c;
    data_021c1c54[11] = data_020d8aa4;
    data_021c1c54[12] = data_020d8ab4;
    data_021c1c54[13] = t;
    data_021c1c54[14] = data_020d8abc;
    data_021c1c54[15] = data_020d8ae4;

    data_021c1cd4[0] = data_020d8af4;
    data_021c1cd4[1] = t;

    data_021c17c4[0] = data_020d86e4;
    data_021c17c4[1] = data_020d86f4;
    data_021c17c4[2] = data_020d86fc;
    data_021c17c4[3] = data_020d8714;
    data_021c17c4[4] = data_020d871c;
    data_021c17c4[5] = data_020d872c;
    data_021c17c4[6] = data_020d8734;
    data_021c17c4[7] = data_020d8754;
    data_021c17c4[8] = data_020d8824;
    data_021c17c4[9] = data_020d876c;

    data_021c1914[0] = data_020d86c4;
    data_021c1914[1] = data_020d86ac;
    data_021c1914[2] = data_020d86a4;
    data_021c1914[3] = data_020d8554;
    data_021c1914[4] = data_020d8684;
    data_021c1914[5] = data_020d857c;
    data_021c1914[6] = data_020d8664;
    data_021c1914[7] = data_020d8594;
    data_021c1914[8] = data_020d864c;
    data_021c1914[9] = data_020d85b4;
    data_021c1914[10] = data_020d894c;
    data_021c1914[11] = data_020d85c4;
    data_021c1914[12] = data_020d85d4;
    data_021c1914[13] = data_020d8614;
    data_021c1914[14] = data_020d85ec;
    data_021c1914[15] = data_020d8674;

    data_021c1994[0] = data_020d86ec;
    data_021c1994[1] = data_020d8704;
    data_021c1994[2] = data_020d8724;
    data_021c1994[3] = data_020d873c;
    data_021c1994[4] = data_020d875c;
    data_021c1994[5] = data_020d877c;
    data_021c1994[6] = data_020d8794;
    data_021c1994[7] = data_020d87a4;
    data_021c1994[8] = data_020d87ec;
    data_021c1994[9] = data_020d88b4;
    data_021c1994[10] = data_020d8964;
    data_021c1994[11] = data_020d89a4;
    data_021c1994[12] = data_020d89b4;
    data_021c1994[13] = data_020d89fc;
    data_021c1994[14] = data_020d8a34;
    data_021c1994[15] = data_020d8aac;

    data_021c1a14[0] = data_020d8a7c;
    data_021c1a14[1] = data_020d869c;
    data_021c1a14[2] = data_020d856c;
    data_021c1a14[3] = data_020d8584;
    data_021c1a14[4] = data_020d85a4;
    data_021c1a14[5] = data_020d8634;
    data_021c1a14[6] = data_020d85e4;
    data_021c1a14[7] = data_020d85fc;
    data_021c1a14[8] = data_020d870c;
    data_021c1a14[9] = data_020d8744;
    data_021c1a14[10] = data_020d8784;
    data_021c1a14[11] = data_020d8b5c;
    data_021c1a14[12] = data_020d88cc;
    data_021c1a14[13] = data_020d89ac;
    data_021c1a14[14] = data_020d89c4;
    data_021c1a14[15] = data_020d8b54;

    data_021c1a94[0] = data_020d853c;
    data_021c1a94[1] = data_020d859c;
    data_021c1a94[2] = data_020d85bc;
    data_021c1a94[3] = data_020d867c;
    data_021c1a94[4] = data_020d874c;
    data_021c1a94[5] = data_020d87f4;
    data_021c1a94[6] = data_020d880c;
    data_021c1a94[7] = data_020d8a14;

    data_021c172c.a = 0;
    data_021c172c.b = -1;
    data_021c1734.a = -1;
    data_021c1734.b = 0;
    data_021c173c.a = 0;
    data_021c173c.b = 1;
    data_021c1744.a = 1;
    data_021c1744.b = 0;
}

#pragma section INIT end
