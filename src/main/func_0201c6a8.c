/* func_0201c6a8 @ 0x0201c6a8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct OtherStruct {
    unsigned char pad_00[0x2c];
    char *unk_2C;
} OtherStruct;

typedef struct UnkStruct_0201c6a8 {
    unsigned char pad_00[0x04];
    OtherStruct *unk_04;
    unsigned char pad_08[0x1c];
    void (*unk_24)(void);
    unsigned char pad_28[0x6a];
    unsigned char unk_92;
} UnkStruct_0201c6a8;

extern void func_02054474(char *addr, UnkStruct_0201c6a8 *self);
extern void func_0201c49c(void);

void func_0201c6a8(UnkStruct_0201c6a8 *self)
{
    if (self->unk_04->unk_2C) {
        func_02054474(self->unk_04->unk_2C + 0xec, self);
    }
    self->unk_24 = func_0201c49c;
    self->unk_92 = 2;
}
