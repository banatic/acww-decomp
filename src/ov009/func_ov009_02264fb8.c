/* func_ov009_02264fb8 @ 0x02264fb8, 0x6c bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02264fb8 {
    unsigned char pad_00[0x136];
    unsigned char unk_136[6];
    unsigned char unk_13C[1];
    unsigned char pad_13D[0xf9];
    unsigned char b0 : 1;
    unsigned char pad_237[1];
    unsigned char unk_238[1];
};

extern void *func_0203efdc(void *self);
extern void func_ov009_02262f0c(void *p);
extern void func_ov009_02264580(struct UnkStruct_02264fb8 *self);
extern void func_ov009_02264398(struct UnkStruct_02264fb8 *self);
extern void func_02055f1c(void *p);
extern void func_ov003_02220240(struct UnkStruct_02264fb8 *self);
extern void func_0203f364(int n);
extern int func_0204bba8(void *p);
extern void func_020ad78c(int n);

int func_ov009_02264fb8(struct UnkStruct_02264fb8 *self)
{
    if (!func_0203efdc(self)) {
        return 0;
    }
    func_ov009_02262f0c(self->unk_238);
    func_ov009_02264580(self);
    func_ov009_02264398(self);
    func_02055f1c(self->unk_13C);
    func_ov003_02220240(self);
    if (self->b0) {
        func_0203f364(self->b0);
        if (func_0204bba8(self->unk_136) != 0) {
            func_020ad78c(1);
        }
    }
    return 1;
}
