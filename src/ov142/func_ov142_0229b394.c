/* func_ov142_0229b394 @ 0x0229b394, 0xa8 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229b394 {
    unsigned char pad_00[0xc0];
    unsigned char byte;
} UnkStruct_0229b394;

extern int func_ov002_02208014(void *receiver);
extern void func_ov142_0229b1fc(UnkStruct_0229b394 *self);
extern char *func_ov002_02208008(UnkStruct_0229b394 *self);
extern int func_ov002_02207fe4(UnkStruct_0229b394 *self);
extern int func_ov002_02207fd8(UnkStruct_0229b394 *self);
extern void func_ov142_0229af4c(UnkStruct_0229b394 *self);
extern void func_ov142_0229aee8(UnkStruct_0229b394 *self);
extern void func_ov142_0229af94(UnkStruct_0229b394 *self);
extern void func_ov142_0229b350(UnkStruct_0229b394 *self);
extern void func_ov142_0229b2f8(UnkStruct_0229b394 *self);
extern unsigned short data_021fbe40[2];

void func_ov142_0229b394(UnkStruct_0229b394 *self)
{
    unsigned char saved;
    unsigned short flags;

    if (func_ov002_02208014(self) != 0) {
        func_ov142_0229b1fc(self);
        return;
    }

    saved = self->byte;
    func_ov002_02208008(self);

    if (func_ov002_02207fe4(self) != 0) {
        self->byte = 0x17;
    } else if (func_ov002_02207fd8(self) != 0) {
        self->byte = 0x18;
    }

    if (saved != self->byte) {
        func_ov142_0229af4c(self);
        return;
    }

    flags = data_021fbe40[1];

    if (flags & 1) {
        func_ov142_0229aee8(self);
        return;
    }

    if (flags & 8) {
        func_ov142_0229af94(self);
        func_ov142_0229b350(self);
    }

    if (data_021fbe40[1] & 2) {
        func_ov142_0229af94(self);
        func_ov142_0229b2f8(self);
    }
}
