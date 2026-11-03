/* post_clerk_4: 7 functions, module ov054
 * mwccarm 1.2/base -O4,s
 * func_ov054_02262494 @ 0x02262494, 0x94 bytes, Thumb
 * func_ov054_02262490 @ 0x02262490, 0x4 bytes, Thumb
 * func_ov054_0226247c @ 0x0226247c, 0x12 bytes, Thumb
 * func_ov054_02262450 @ 0x02262450, 0x2c bytes, Thumb
 * func_ov054_02262430 @ 0x02262430, 0x1e bytes, Thumb
 * func_ov054_022623c8 @ 0x022623c8, 0x68 bytes, Thumb
 * func_ov054_02262368 @ 0x02262368, 0x60 bytes, Thumb
 */

struct MainObj {
    char pad_00[0x80C];
    int unk_80C;
};

struct TableEntry {
    int a, b, c;
};

struct UnkStruct_022623c8 {
    char pad_00[0x564];
    char data[0x2AC];
    unsigned short unk_810;
    unsigned short unk_812;
    unsigned char unk_814;
};

struct UnkStruct_02262368 {
    char pad_00[0x350];
    char buf350[0x4bc];
    int unk_80C;
    unsigned short unk_810;
};

extern int *func_02095794(int);
extern void func_0204f818(int *lo, int *hi, const void *in);
extern struct TableEntry data_ov054_022629c8[2];
extern int func_0203e0a8(int a, int b);
extern int func_02095ab0(void *dst, int size, int count);
extern int func_0209615c(int);
extern void func_ov054_02262528(int, int);
extern int func_02019c6c(char *p, int n, unsigned short v);
extern int func_0202ea40(void *self, void *local, int flag);
extern int func_020644cc(int v);
extern unsigned short data_020c80f8;
extern int func_ov054_02260474(void *self);
extern void func_0201af1c(void *buf, int byteval);
extern int func_020e8840(void *ptr);
extern unsigned char data_ov054_0226297c[];

int func_ov054_02262494(struct MainObj *self)
{
    int out1_lo, out1_hi;
    int out2_lo, out2_hi;
    int input[3];
    struct TableEntry tempEntry;
    int *data;
    int original;
    int i;

    data = func_02095794(4);
    input[0] = data[0];
    input[1] = data[1];
    input[2] = data[2];

    out1_lo = 0;
    out1_hi = 0;
    func_0204f818(&out1_lo, &out1_hi, input);

    original = self->unk_80C;

    i = 0;
    while (i < 2) {
        out2_lo = 0;
        out2_hi = 0;
        tempEntry.a = data_ov054_022629c8[i].a;
        tempEntry.b = data_ov054_022629c8[i].b;
        tempEntry.c = data_ov054_022629c8[i].c;
        func_0204f818(&out2_lo, &out2_hi, &tempEntry);
        if (out1_lo == out2_lo && out1_hi == out2_hi) {
            self->unk_80C = i;
            break;
        }
        i++;
    }

    if (original != self->unk_80C) {
        return 1;
    } else {
        return 0;
    }
}

int func_ov054_02262490(void)
{
    return 1;
}

int func_ov054_0226247c(int a)
{
    func_0203e0a8(a, 0);
    return 1;
}

int func_ov054_02262450(void)
{
    unsigned int local[3];
    int i;

    local[0] = ((unsigned int *) data_ov054_022629c8)[0];
    local[1] = ((unsigned int *) data_ov054_022629c8)[1];
    local[2] = ((unsigned int *) data_ov054_022629c8)[2];
    func_02095ab0(local, 0x400, 4);
    return 1;
}

int func_ov054_02262430(int param)
{
    if (func_0209615c(4) == 0) {
        func_ov054_02262528(param, 4);
    }
    return 1;
}

int func_ov054_022623c8(struct UnkStruct_022623c8 *self)
{
    unsigned char local[8];
    func_02019c6c(self->data, 1, self->unk_812);
    self->unk_810 = 0xFF;
    if (self->unk_814 == 0) {
        if (func_0202ea40((void *) self, local, 0) != 0) {
            self->unk_810 = (unsigned short) (func_020644cc(5) * 20 + 100);
        }
    }
    self->unk_812 = data_020c80f8;
    return 1;
}

int func_ov054_02262368(struct UnkStruct_02262368 *self)
{
    if (func_ov054_02260474(self) != 0) {
        goto end;
    }
    if (func_ov054_02262494((struct MainObj *) self) != 0) {
        func_ov054_02262528((int) self, 3);
        func_0201af1c(&self->buf350, data_ov054_0226297c[self->unk_80C]);
    }
    if (self->unk_810 == 0xff) {
        goto end;
    }
    if (func_020e8840(&self->unk_810) != 0) {
        goto end;
    }
    func_ov054_02262528((int) self, 7);
end:
    return 1;
}
