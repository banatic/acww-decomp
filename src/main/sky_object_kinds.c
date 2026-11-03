/* sky_object_kinds: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020bf2b8 @ 0x020bf2b8, 0x50 bytes, Thumb
 * func_020bf2a0 @ 0x020bf2a0, 0x18 bytes, Thumb
 * func_020bf290 @ 0x020bf290, 0xe bytes, Thumb
 * func_020bf26c @ 0x020bf26c, 0x24 bytes, Thumb
 * func_020bf248 @ 0x020bf248, 0x24 bytes, Thumb
 * func_020bf220 @ 0x020bf220, 0x28 bytes, Thumb
 */

struct Input {
    char pad_00[0x34];
    unsigned int unk_34;
    unsigned int unk_38;
};

struct Output {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
};

extern int FX_MulFunc(int, int);
extern int FX_Div(int, int);
extern void func_020be5d0(void *, int, void *, void *);
extern unsigned char data_021fbb14[];
extern void func_020be5a0(void *, int, int, void *);

void func_020bf2b8(int *out, int a, int b, int size)
{
    int x = FX_MulFunc(0x400, size);
    int y = FX_MulFunc(0x1000, size);
    int z = FX_Div(0x1000 - x, y - x);
    if (z < 0) {
        z = 0;
    } else if (z > 0x1000) {
        z = 0x1000;
    }
    out[0] = a;
    out[1] = b;
    out[2] = z;
}

void func_020bf2a0(int a0, int a1)
{
    int r3 = a0;
    int r0 = a1;
    int r1 = *(int *) (r3 + 0x34);
    int r2 = *(int *) (r3 + 0x38);
    int r3_2 = *(int *) (r3 + 0x4c);
    func_020bf2b8((int *) r0, r1, r2, r3_2);
}

int func_020bf290(struct Input *in, struct Output *out)
{
    out->unk_00 = in->unk_34;
    out->unk_04 = in->unk_38;
    out->unk_08 = 0;
    return 0;
}

void func_020bf26c(void *arg0, void *arg1)
{
    int local[4];
    func_020bf2a0((int) arg0, (int) local);
    func_020be5d0((void *) data_021fbb14, 0, arg1, local);
}

void func_020bf248(int a, int b)
{
    char buffer[16];
    func_020bf2a0(a, (int) buffer);
    func_020be5a0(((int *) data_021fbb14), 0, b, buffer);
}

void func_020bf220(int a, int b, int c)
{
    int buffer[3];
    func_020bf290((struct Input *) a, (struct Output *) buffer);
    func_020be5d0((void *) (((int *) data_021fbb14)), b, (void *) c, (void *) buffer);
}
