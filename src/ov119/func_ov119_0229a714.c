/* func_ov119_0229a714 @ 0x0229a714, 0x50 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov119_0229a46c(void *);
extern void func_ov119_0229aa18(void *);
extern void func_ov119_0229aacc(void *);
extern void func_ov119_0229a410(void *, int);
extern void func_ov119_0229a764(void *);

struct UnkStruct_0229a714 {
    unsigned char pad_00[0x9c];
    unsigned char unk_9C;
    unsigned char pad_9D[0x12];
    unsigned char unk_AF;
    unsigned char pad_B0[2];
    unsigned char unk_B2;
    unsigned char unk_B3;
};

void func_ov119_0229a714(struct UnkStruct_0229a714 *self)
{
    self->unk_B2 = 0;
    self->unk_B3 = 0;
    func_ov119_0229a46c(self);
    self->unk_AF = 0;
    if (self->unk_9C == 4) {
        goto case4;
    }
    if (self->unk_9C == 5) {
        func_ov119_0229aacc(self);
        goto end;
    } else {
        goto other;
    }
case4:
    func_ov119_0229aa18(self);
    goto end;
other:
    func_ov119_0229a410(self, 4);
    func_ov119_0229a764(self);
end:;
}
