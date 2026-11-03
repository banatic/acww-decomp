/* sky_sound: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020bbee0 @ 0x020bbee0, 0x14 bytes, Thumb
 * func_020bbe94 @ 0x020bbe94, 0x4c bytes, Thumb
 * func_020bbe8c @ 0x020bbe8c, 0x8 bytes, Thumb
 * func_020bbe38 @ 0x020bbe38, 0x54 bytes, Thumb
 * func_020bbdc8 @ 0x020bbdc8, 0x70 bytes, Thumb
 */

struct UnkStruct_020bbe94 {
    long long unk_00;
    int unk_08;
};

typedef struct {
    char pad_00[0x0c];
    int unk_0C;
} Param;

extern int func_0200430c(int arg);
extern int func_020b6840(int);
extern void func_02004290(void *p, int val);
extern char *func_02137550(void *ptr, int size);
extern void func_020042b0(void *p, void *local);
extern int data_020d2334[];
extern void func_02004280(void *);
extern struct {
    char pad0[0x24];
    unsigned int f24;
    char pad1[0x0c];
    unsigned int f34;
} data_021f8ab0;
extern int func_020e88dc(int *ptr, int a, int b);

void func_020bbe38(unsigned int *out);
void func_020bbdc8(Param *p);

int func_020bbee0(int arg)
{
    func_020bbe38((unsigned int *) arg);
    return func_0200430c(arg);
}

void func_020bbe94(void *p)
{
    struct UnkStruct_020bbe94 local;

    if (*(int *) ((char *) p + 0xc) != 0) {
        int idx = func_020b6840(0);
        int v = data_020d2334[idx];
        if (v >= 0) {
            func_02004290(p, v);
        }
    }

    func_02137550(&local, 0xc);
    local.unk_08 = *(int *) ((char *) p + 0xc) >> 8;
    func_020042b0(p, &local);
    func_020bbdc8((Param *) p);
}

void func_020bbe8c(void *argument0)
{
    func_02004280((void *) argument0);
}

void func_020bbe38(unsigned int *out)
{
    unsigned int x;
    unsigned int y;
    int a;
    int b;
    int c;

    x = data_021f8ab0.f24;
    a = (x == 3);
    b = (x == 4);
    y = data_021f8ab0.f34;
    c = (y == 1);

    out[3] = 0;

    if (c) {
        if (a) {
            out[3] = 0x00099a00;
        } else if (b) {
            out[3] = 0x00100000;
        }
    }
}

void func_020bbdc8(Param *p)
{
    int v_28;
    int v_3;
    int v_4;
    int v_34_is1;
    int r1;
    int r2;

    v_28 = (*(struct { char pad0[0x28]; int field_0x28; char pad1[8]; int field_0x34; } *) &data_021f8ab0).field_0x28;
    v_3 = (v_28 == 3) ? 1 : 0;
    v_4 = (v_28 == 4) ? 1 : 0;
    v_34_is1 = ((*(struct { char pad0[0x28]; int field_0x28; char pad1[8]; int field_0x34; } *) &data_021f8ab0).field_0x34 == 1) ? 1 : 0;
    r1 = 0;
    if (v_34_is1) {
        if (v_3) {
            r1 = 0x099a00;
        } else if (v_4) {
            r1 = 0x100000;
        }
    }
    r2 = 0xdf;
    if (v_34_is1) {
        if (r1 < p->unk_0C) {
            r2 = 0x1eb;
        }
    } else {
        r2 = 0x5200;
    }
    func_020e88dc(&p->unk_0C, r1, r2);
}
