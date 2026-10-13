/* func_0209c0a0 @ 0x0209c0a0, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0209c0a0 {
    unsigned char unk_00[3];
    unsigned char unk_03;
    unsigned char unk_04[4];
    unsigned char unk_08[8];
    unsigned char unk_10;
    unsigned char unk_11[16];
    unsigned char unk_21;
};

extern int func_0209c4a8(void *ptr);
extern int func_0209c38c(int val);
extern void func_0209c32c(struct UnkStruct_0209c0a0 *self, int val);
extern void func_0209c470(void *ptr, int val);
extern void func_0209e474(struct UnkStruct_0209c0a0 *self);
extern void MI_CpuCopy8(void *dst, void *src, int size);

int func_0209c0a0(struct UnkStruct_0209c0a0 *self, unsigned char *other)
{
    int x;

    if (self->unk_10 != 0xb) {
        goto fail;
    }
    if (other[3] == self->unk_03) {
        goto fail;
    }

    x = func_0209c4a8(self->unk_11);
    if (func_0209c38c(x) == 0) {
        goto fail;
    }

    func_0209c32c(self, x);
    func_0209c470(self->unk_11, x);
    self->unk_21 &= ~1;
    func_0209e474(self);
    MI_CpuCopy8(self, self->unk_08, 8);

    return x;

fail:
    return 0xc;
}
