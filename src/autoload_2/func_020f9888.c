/* func_020f9888 @ 0x020f9888, 0x60 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern char data_0213f25c;
extern void func_0210b500(int, int);

struct Object {
    void *vtbl;
    int unk_04;
    char unk_08;
    char unk_09;
    char unk_0A;
    char unk_0B;
    char unk_0C;
    unsigned short unk_0E;
    char unk_10;
};

struct Object *func_020f9888(struct Object *self)
{
    self->vtbl = &data_0213f25c;
    self->unk_04 = 0;
    self->unk_08 = 0;
    self->unk_09 = 0;
    self->unk_0A = 0;
    self->unk_0B = -1;
    self->unk_0C = -1;
    self->unk_0E = 0x78;
    self->unk_10 = -1;
    func_0210b500(2, -1);
    func_0210b500(1, -1);
    return self;
}
