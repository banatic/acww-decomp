/* func_ov120_0229b1b0 @ 0x0229b1b0, 0x64 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229b1b0 {
    char pad_00[0xa9];
    unsigned char unk_A9;
    char pad_AA[0x720 - 0xaa];
    char sub;
};

extern void func_ov120_0229b4b0(struct UnkStruct_0229b1b0 *);
extern void func_ov120_0229b308(struct UnkStruct_0229b1b0 *);
extern int func_ov120_0229b14c(struct UnkStruct_0229b1b0 *);
extern void func_ov120_0229a428(struct UnkStruct_0229b1b0 *, int);
extern void func_ov120_0229a438(struct UnkStruct_0229b1b0 *, int);
extern void func_0206fdd4(char *, int, int, int, int, int);
extern void func_ov120_0229ad5c(struct UnkStruct_0229b1b0 *, unsigned char);

void func_ov120_0229b1b0(struct UnkStruct_0229b1b0 *self)
{
    int result;
    int flag;

    func_ov120_0229b4b0(self);
    func_ov120_0229b308(self);
    result = func_ov120_0229b14c(self);

    if (result == 0) {
        func_ov120_0229a428(self, 8);
        flag = 4;
    } else {
        func_ov120_0229a438(self, 8);
        flag = 3;
    }

    func_0206fdd4(&self->sub, 0x1d, 0xa, 0x1d, 0x15, flag);
    func_ov120_0229a438(self, 0x20);
    func_ov120_0229ad5c(self, self->unk_A9);
}
