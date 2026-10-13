/* func_020f55cc @ 0x020f55cc, 0x40 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f5970(void *self);
extern void func_020f555c(void);
extern char data_020d8414;

struct UnkStruct_020f55cc {
    void *unk_00;
    unsigned char pad_04[0x30];
    void (*unk_34)(void);
    unsigned char pad_38[0x6];
    unsigned char unk_3E;
    unsigned char unk_3F;
};

struct UnkStruct_020f55cc *func_020f55cc(struct UnkStruct_020f55cc *self)
{
    func_020f5970(self);
    self->unk_00 = &data_020d8414;
    self->unk_34 = func_020f555c;
    self->unk_3E = 1;
    self->unk_3F = 0;
    return self;
}
