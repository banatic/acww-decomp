/* func_020f560c @ 0x020f560c, 0x40 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020f560c;

extern void func_020f5970(struct UnkStruct_020f560c *self);
extern void func_020f555c(void);
extern char data_020d8414;

typedef struct UnkStruct_020f560c {
    void *unk_00;
    unsigned char pad_04[0x30];
    void (*unk_34)(void);
    unsigned char pad_38[0x06];
    unsigned char unk_3E;
    unsigned char unk_3F;
} UnkStruct_020f560c;

struct UnkStruct_020f560c *func_020f560c(struct UnkStruct_020f560c *self)
{
    func_020f5970(self);
    self->unk_00 = &data_020d8414;
    self->unk_34 = func_020f555c;
    self->unk_3E = 1;
    self->unk_3F = 0;
    return self;
}
