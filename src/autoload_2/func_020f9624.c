/* func_020f9624 @ 0x020f9624, 0x5c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020f9624 {
    char a;
    unsigned char pad_15[0x13];
    char b;
    char d;
    char c;
    unsigned char pad_17[1];
    short e;
    char unk_1A;
};

struct UnkStruct_020f9624_2 {
    void *vtbl;
    unsigned char pad_04[0x10];
    struct UnkStruct_020f9624 sub;
};

extern void *func_020f98e8(struct UnkStruct_020f9624_2 *self);
extern void func_020f9680(struct UnkStruct_020f9624 *p);
extern int data_0213f250;
extern struct UnkStruct_020f9624_2 *data_021fd1bc;

struct UnkStruct_020f9624_2 *func_020f9624(struct UnkStruct_020f9624_2 *self)
{
    func_020f98e8(self);
    self->vtbl = &data_0213f250;
    func_020f9680(&self->sub);
    self->sub.a = -1;
    self->sub.b = 0;
    self->sub.c = 0;
    self->sub.d = 1;
    self->sub.e = -1;
    self->sub.unk_1A = 1;
    data_021fd1bc = self;
    return self;
}
