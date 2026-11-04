/* music_beat_3: 4 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f98e8 @ 0x020f98e8, 0x60 bytes, ARM
 * func_020f9888 @ 0x020f9888, 0x60 bytes, ARM
 * func_020f9868 @ 0x020f9868, 0x20 bytes, ARM
 * func_020f9848 @ 0x020f9848, 0x20 bytes, ARM
 */

struct UnkStruct_020f98e8 {
    void *unk_00;
    int unk_04;
    unsigned char unk_08;
    unsigned char unk_09;
    unsigned char unk_0A;
    signed char unk_0B;
    signed char unk_0C;
    unsigned short unk_0E;
    signed char unk_10;
};

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

extern int func_0210b500(int, int);
extern unsigned char data_0213f25c[];
extern int data_021fd1bc;

void *func_020f98e8(struct UnkStruct_020f98e8 *r4)
{
    r4->unk_00 = (void *) data_0213f25c;
    r4->unk_04 = 0;
    r4->unk_08 = 0;
    r4->unk_09 = 0;
    r4->unk_0A = 0;
    r4->unk_0B = -1;
    r4->unk_0C = -1;
    r4->unk_0E = 0x78;
    r4->unk_10 = -1;
    func_0210b500(2, -1);
    func_0210b500(1, -1);
    return r4;
}

struct Object *func_020f9888(struct Object *self)
{
    self->vtbl = ((char *) data_0213f25c);
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

unsigned int *func_020f9868(unsigned int *arg0)
{
    *arg0 = (unsigned int) ((char *) data_0213f25c);
    data_021fd1bc = 0;
    return arg0;
}

unsigned int *func_020f9848(unsigned int *out)
{
    *out = (unsigned int) ((int *) data_0213f25c);
    data_021fd1bc = 0;
    return out;
}
