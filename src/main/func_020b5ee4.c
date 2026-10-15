/* func_020b5ee4 @ 0x020b5ee4, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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

extern unsigned int data_021f6934;
extern int data_020ca0f0;
extern int data_021f6940;

extern int func_02095fc0(UnkStruct_020b5ee4_2 *outA, UnkStruct_020b5ee4 *outC);
extern void func_0204f818(int *out1, int *out2, UnkStruct_020b5ee4_2 *outA);
extern int func_020b65c4(void);
extern int func_020b5e10(void);
extern int func_020b5f84(int a, int b, UnkStruct_020b5ee4_2 *c, unsigned int d, int e, int f, int g);

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

    return func_020b5f84(b, r1, &local18, ((unsigned int) r4 << 22) & 0x3fc00000, localc.unk_00, out10, out14);
}
