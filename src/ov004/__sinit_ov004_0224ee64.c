/* __sinit_ov004_0224ee64 @ 0x0224ee64, 0x204 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} UnkStruct_0224ee64;
typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_0224ee64_2;

extern void __register_global_object(UnkStruct_0224ee64_2 *, void *destructor, void *);
extern void func_020012dc(void *arg0);
extern UnkStruct_0224ee64_2 data_ov004_022593dc, data_ov004_022593c4;
extern int data_ov004_022593d0, data_ov004_022593e8;
extern UnkStruct_0224ee64 data_ov004_02259424[4];
extern UnkStruct_0224ee64 data_ov004_02255c50;
extern UnkStruct_0224ee64 data_ov004_02255c58;
extern UnkStruct_0224ee64 data_ov004_02255c40;
extern UnkStruct_0224ee64 data_ov004_02255cc8;
extern UnkStruct_0224ee64 data_ov004_0225949c[7];
extern UnkStruct_0224ee64 data_ov004_02255c60;
extern UnkStruct_0224ee64 data_ov004_02255c88;
extern UnkStruct_0224ee64 data_ov004_02255d10;
extern UnkStruct_0224ee64 data_ov004_02255c70;
extern UnkStruct_0224ee64 data_ov004_02255d18;
extern UnkStruct_0224ee64 data_ov004_02255c68;
extern UnkStruct_0224ee64 data_ov004_02255ca0;
extern UnkStruct_0224ee64 data_ov004_0225946c[6];
extern UnkStruct_0224ee64 data_ov004_02255d08;
extern UnkStruct_0224ee64 data_ov004_02255cd0;
extern UnkStruct_0224ee64 data_ov004_02255cf8;
extern UnkStruct_0224ee64 data_ov004_02255cd8;
extern UnkStruct_0224ee64 data_ov004_02255ce8;
extern UnkStruct_0224ee64 data_ov004_02255cc0;
extern UnkStruct_0224ee64 data_ov004_02259444[5];
extern UnkStruct_0224ee64 data_ov004_02255cf0;
extern UnkStruct_0224ee64 data_ov004_02255ce0;
extern UnkStruct_0224ee64 data_ov004_02255c48;
extern UnkStruct_0224ee64 data_ov004_02255cb8;
extern UnkStruct_0224ee64 data_ov004_02255c38;
extern UnkStruct_0224ee64 data_ov004_022593f4[3];
extern UnkStruct_0224ee64 data_ov004_02255ca8;
extern UnkStruct_0224ee64 data_ov004_02255c98;
extern UnkStruct_0224ee64 data_ov004_02255c90;
extern UnkStruct_0224ee64 data_ov004_0225940c[3];
extern UnkStruct_0224ee64 data_ov004_02255c78;
extern UnkStruct_0224ee64 data_ov004_02255c80;
extern UnkStruct_0224ee64 data_ov004_02255cb0;

void __sinit_ov004_0224ee64(void)
{
    UnkStruct_0224ee64_2 *p;
    p = &data_ov004_022593dc;
    p->a = 0x11000;
    p->b = 0;
    p->c = 0x15000;
    __register_global_object(p, ((void *) &func_020012dc), &data_ov004_022593d0);
    p = &data_ov004_022593c4;
    p->a = 0x11000;
    p->b = 0;
    p->c = 0x7000;
    __register_global_object(p, ((void *) &func_020012dc), &data_ov004_022593e8);

    data_ov004_02259424[0] = data_ov004_02255c50;
    data_ov004_02259424[1] = data_ov004_02255c58;
    data_ov004_02259424[2] = data_ov004_02255c40;
    data_ov004_02259424[3] = data_ov004_02255cc8;
    data_ov004_0225949c[0] = data_ov004_02255c60;
    data_ov004_0225949c[1] = data_ov004_02255c88;
    data_ov004_0225949c[2] = data_ov004_02255d10;
    data_ov004_0225949c[3] = data_ov004_02255c70;
    data_ov004_0225949c[4] = data_ov004_02255d18;
    data_ov004_0225949c[5] = data_ov004_02255c68;
    data_ov004_0225949c[6] = data_ov004_02255ca0;
    data_ov004_0225946c[0] = data_ov004_02255d08;
    data_ov004_0225946c[1] = data_ov004_02255cd0;
    data_ov004_0225946c[2] = data_ov004_02255cf8;
    data_ov004_0225946c[3] = data_ov004_02255cd8;
    data_ov004_0225946c[4] = data_ov004_02255ce8;
    data_ov004_0225946c[5] = data_ov004_02255cc0;
    data_ov004_02259444[0] = data_ov004_02255cf0;
    data_ov004_02259444[1] = data_ov004_02255ce0;
    data_ov004_02259444[2] = data_ov004_02255c48;
    data_ov004_02259444[3] = data_ov004_02255cb8;
    data_ov004_02259444[4] = data_ov004_02255c38;
    data_ov004_022593f4[0] = data_ov004_02255ca8;
    data_ov004_022593f4[1] = data_ov004_02255c98;
    data_ov004_022593f4[2] = data_ov004_02255c90;
    data_ov004_0225940c[0] = data_ov004_02255c78;
    data_ov004_0225940c[1] = data_ov004_02255c80;
    data_ov004_0225940c[2] = data_ov004_02255cb0;
}
