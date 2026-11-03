/* scene_place: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b5f84 @ 0x020b5f84, 0x44 bytes, Thumb
 * func_020b5ee4 @ 0x020b5ee4, 0xa0 bytes, Thumb
 * func_020b5ea0 @ 0x020b5ea0, 0x44 bytes, Thumb
 * func_020b5e90 @ 0x020b5e90, 0x10 bytes, Thumb
 */

typedef struct {
    short unk_00;
    short pad_02;
} UnkStruct_020b5ee4;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_020b5ee4_2;

extern int data_021f69a0;
extern int func_020b64c0(int);
extern void func_020b64f0(int *p, int b, int c, int d, int e, int f, int g);
extern unsigned int data_021f6934;
extern int data_020ca0f0;
extern int data_021f6940;
extern int func_02095fc0(UnkStruct_020b5ee4_2 *outA, UnkStruct_020b5ee4 *outC);
extern void func_0204f818(int *out1, int *out2, UnkStruct_020b5ee4_2 *outA);
extern int func_020b65c4(void);
extern int func_020b5e10(void);
extern int data_021f69b8;
extern void func_020b6518(int);

int func_020b5f84(int a, int b, int c, int d, short e, int f, int g)
{
    if (func_020b64c0(b)) {
        func_020b64f0(&data_021f69a0, b, c, d, (int) e, f, g);
        return 1;
    }
    return 0;
}

int func_020b5ee4(int unused, int b)
{
    UnkStruct_020b5ee4_2 local18;
    UnkStruct_020b5ee4 localc;
    int out10, out14;
    int r4;
    int r1;
    unsigned int flags;

    flags = data_021f6934;
    if ((flags & 1) == 0) {
        data_021f6940 = data_020ca0f0 + 0x1000;
        data_021f6934 = flags | 1;
    }

    r4 = func_02095fc0(&local18, &localc);
    out10 = 0;
    out14 = 0;
    func_0204f818(&out10, &out14, &local18);

    if (func_020b65c4() == 0xb) {
        if (local18.unk_08 < data_021f6940) {
            local18.unk_08 = data_021f6940;
        }
    }
    local18.unk_08 = local18.unk_08 + b;

    b = func_020b5e10();
    r1 = func_020b65c4();

    return func_020b5f84(b, r1, (int) (&local18), ((unsigned int) r4 << 22) & 0x3fc00000, localc.unk_00, out10, out14);
}

int func_020b5ea0(int p0, int p1, int p2, int p3, short p4, int p5, int p6)
{
    if (func_020b64c0(p1)) {
        func_020b64f0((int *) ((int) &data_021f69b8), p1, p2, p3, (int) p4, p5, p6);
        return 1;
    } else {
        return 0;
    }
}

void func_020b5e90(void)
{
    func_020b6518((int) &data_021f69b8);
}
