/* func_020c0494 @ 0x020c0494, 0x1c4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;

typedef struct UnkStruct_020c0494 UnkStruct_020c0494;
struct UnkStruct_020c0494 {
    char pad_00[4];
    int unk_04;
    int unk_08;
    int unk_0C;
    char sub10[0x24 - 0x10];
    int unk_24;
    char pad_28[0x2e - 0x28];
    unsigned char unk_2E;
    char pad_2F[0x34 - 0x2f];
    Vec unk_34;
    Vec unk_40;
    int unk_4C;
    int unk_50;
    char pad_54[0x60 - 0x54];
    int unk_60;
    int unk_64;
};

extern Vec data_021fa678[];
extern int data_021fbaf0;
extern int func_020bf514(UnkStruct_020c0494 *p, int a, int b, int c);
extern int func_020bf308(UnkStruct_020c0494 *p, int a, int b, int c);
extern void func_020bee60(Vec *v, int n);
extern void func_020beb20(int *g);
extern void func_020bf26c(UnkStruct_020c0494 *p, int a);
extern int func_0208a1cc(void *p);
extern void func_020bf5b8(UnkStruct_020c0494 *p);
extern void func_0208a158(void *p);
extern void func_020c0688(Vec *a, int b, int c);
extern int FX_MulFunc(int a, int b);
extern void func_0208a144(void *p);
extern void func_020eabc8(Vec *a, int b);
extern void VEC_Add(Vec *a, Vec *b, Vec *c);
extern void func_020beb14(int *g);
extern void func_02040ba0(int a);
extern void func_020beb00(int *g, int a, int b, int c, int d);

void func_020c0494(UnkStruct_020c0494 *p)
{
    int n;
    int old;

    if (p->unk_60 == 0) {
        if (func_020bf514(p, 0x30a, 0x8000, -100) != 0) {
            p->unk_04 = 3;
        } else if (func_020bf308(p, 0x1b000, 0x15000, 0) != 0) {
            n = p->unk_08 + 1;
            func_020bee60(&data_021fa678[p->unk_24], n);
            p->unk_08 = n;
            func_020beb20(&data_021fbaf0);
            func_020bf26c(p, 0x7ff);
            p->unk_60 = 1;
            p->unk_64 = 0;
        } else if (func_0208a1cc(&p->sub10) == 0) {
            old = p->unk_64;
            p->unk_64 = old + 1;
            if (old == 0) {
                func_020bf26c(p, 0x7fe);
            }
        } else {
            p->unk_64 = 0;
        }
    } else if (p->unk_60 == 1) {
        p->unk_0C = 0x14;
        func_020bf5b8(p);
        func_0208a158(&p->sub10);
        p->unk_40.x = p->unk_2E != 0 ? 0x3c00 : -0x3c00;
        p->unk_40.y = -0x4000;
        p->unk_40.z = 0;
        func_020c0688(&p->unk_34, p->unk_4C, p->unk_40.x);
        p->unk_4C = FX_MulFunc(p->unk_4C, 0xe8c);
        p->unk_50 = FX_MulFunc(p->unk_50, 0xe8c);
        p->unk_60 = 2;
        p->unk_64 = 0;
    } else if (p->unk_60 == 2) {
        p->unk_64++;
        if (p->unk_64 >= 1) {
            p->unk_4C = FX_MulFunc(p->unk_4C, 0x119a);
            p->unk_50 = FX_MulFunc(p->unk_50, 0x119a);
            p->unk_60 = 6;
            p->unk_64 = 0;
            func_0208a144(&p->sub10);
        }
    }
    if (p->unk_60 >= 6) {
        p->unk_40.y = p->unk_40.y + 0x59a;
        func_020eabc8(&p->unk_40, 0x1000);
        VEC_Add(&p->unk_34, &p->unk_40, &p->unk_34);
    }
    if (p->unk_60 >= 6) {
        if (p->unk_34.y > 0xd0000) {
            func_020beb14(&data_021fbaf0);
            func_02040ba0(0x45);
            p->unk_04 = 3;
        }
    }
    if (p->unk_60 >= 1) {
        func_020beb00(&data_021fbaf0, p->unk_34.x, p->unk_34.y, p->unk_4C, p->unk_2E != 0 ? 0 : 1);
    }
}
