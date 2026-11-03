/* fader: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b3740 @ 0x020b3740, 0xa bytes, Thumb
 * func_020b373c @ 0x020b373c, 0x2 bytes, Thumb
 * func_020b3720 @ 0x020b3720, 0x1c bytes, Thumb
 * func_020b36c8 @ 0x020b36c8, 0x58 bytes, Thumb
 * func_020b3670 @ 0x020b3670, 0x58 bytes, Thumb
 * func_020b365c @ 0x020b365c, 0x12 bytes, Thumb
 * func_020b3658 @ 0x020b3658, 0x4 bytes, Thumb
 */

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned short unk_10;
    unsigned short unk_12;
} UnkStruct_020b36c8;

struct UnkStruct_020b3670 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    short unk_10;
    short unk_12;
};

extern unsigned int data_020d1e90[];
extern int func_020e895c(UnkStruct_020b36c8 *self, unsigned int a, unsigned int b);
extern int FX_MulFunc(int, int);

int func_020b3670(struct UnkStruct_020b3670 *o, int a, int b, int c, int d);

void func_020b3740(int *p)
{
    p[0] = 0;
    p[1] = 0;
    p[3] = 0;
}

void func_020b373c(void *object) {}

void func_020b3720(int a, int b)
{
    func_020b3670((struct UnkStruct_020b3670 *) a, b, 0, 0, 0x800);
}

void func_020b36c8(UnkStruct_020b36c8 *self)
{
    if (self->unk_0C == 1) {
        if (self->unk_12 != 0) {
            self->unk_00 = 0;
            self->unk_12--;
        }
        if (self->unk_12 != 0) {
            return;
        }
        if (self->unk_10 < 0xb) {
            self->unk_00 = data_020d1e90[self->unk_10];
            self->unk_10++;
        } else {
            self->unk_0C = 0;
            self->unk_10 = 0;
        }
    } else {
        if (self->unk_04 != self->unk_00) {
            func_020e895c(self, self->unk_04, self->unk_08);
        }
    }
}

int func_020b3670(struct UnkStruct_020b3670 *o, int a, int b, int c, int d)
{
    o->unk_08 = d;
    if (a != 0) {
        if (o->unk_04 != 0) {
            goto fail;
        }
        o->unk_04 = 0x1000;
        if (b == 0) {
            o->unk_00 = 0x1000;
            return 0;
        } else {
            if (c != 0) {
                o->unk_0C = 1;
                o->unk_10 = 0;
                o->unk_12 = 5;
            }
            return 1;
        }
    } else {
        o->unk_0C = 0;
        if (o->unk_04 == 0) {
            goto fail;
        }
        o->unk_04 = 0;
        if (b == 0) {
            o->unk_00 = 0;
            return 0;
        } else {
            return 1;
        }
    }
fail:
    return 0;
}

int func_020b365c(int a, int b, int c)
{
    int d = c - b;
    return b + FX_MulFunc(a, d);
}

int func_020b3658(int *p0)
{
    return p0[0];
}
