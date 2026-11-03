/* title_scene_4: 3 functions, module ov147
 * mwccarm 1.2/base -O4,s
 * func_ov147_0229a054 @ 0x0229a054, 0x3a bytes, Thumb
 * func_ov147_0229a01c @ 0x0229a01c, 0x38 bytes, Thumb
 * func_ov147_0229a000 @ 0x0229a000, 0x1c bytes, Thumb
 */

typedef struct {
    char pad_00[0xa3];
    unsigned char unk_A3;
} UnkStruct_0229a01c;

struct UnkStruct_0229a000_2 {
    unsigned char pad_00[0xa3];
    unsigned char byte_at_a3;
};

struct UnkStruct_0229a000 {
    unsigned char pad_00[0x248];
    int unk_248;
};

extern void func_02035684(int, int, int);
extern void func_020356c4(int, int, int, int);
extern void func_02035638(int);
extern void func_02035624(int);
extern struct UnkStruct_0229a000 *data_021c526c;

void func_ov147_0229a054(int r0, int r1)
{
    int r4 = r0;
    if (*(unsigned char *) (r0 + 0xa3) == 0) {
        if (r1 != 0) {
            func_02035684(1, 0xf, 0);
            *(unsigned char *) (r4 + 0xa3) = 2;
        } else {
            func_020356c4(2, 0, 0x7f, 0);
            *(unsigned char *) (r4 + 0xa3) = 1;
        }
    }
}

void func_ov147_0229a01c(UnkStruct_0229a01c *self)
{
    unsigned char val = self->unk_A3;
    if (val == 0) {
        return;
    }
    if (val == 1) {
        func_02035638(0);
    } else if (val == 2) {
        func_02035624(1);
    }
    func_02035684(1, 0xf, 0xf);
    self->unk_A3 = 0;
}

void func_ov147_0229a000(struct UnkStruct_0229a000_2 *self)
{
    if (self->byte_at_a3 == 1) {
        data_021c526c->unk_248 = 0xb;
    }
}
