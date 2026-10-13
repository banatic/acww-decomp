/* func_0208df44 @ 0x0208df44, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208af30(void *self);
extern void func_0208a1f8(char *sub);
extern void func_0208e024(char *sub);
extern char data_020e226c;

struct UnkStruct_0208df44 {
    char *unk_00;
    char pad_04[8];
    char sub1[20];
    int words[10];
    char bytes[8];
    int unk_50;
    int unk_54;
    int unk_58;
    int unk_5C;
    unsigned short unk_60;
    unsigned short unk_62;
    int unk_64;
    char sub68[0x1c];
    char sub84[0x1c];
    char suba0[0x1c];
    char subbc[0x1c];
};

struct UnkStruct_0208df44 *func_0208df44(struct UnkStruct_0208df44 *self)
{
    func_0208af30(self);
    self->unk_00 = &data_020e226c;
    func_0208a1f8(self->sub1);
    self->words[0] = 0;
    self->words[1] = 0;
    self->words[2] = 0;
    self->words[3] = 0;
    self->words[4] = 0;
    self->words[5] = 0;
    self->words[6] = 0;
    self->words[7] = 0;
    self->words[8] = 0;
    self->words[9] = 0;
    self->bytes[0] = 0;
    self->bytes[1] = 0;
    self->bytes[2] = 0;
    self->bytes[3] = 0;
    self->bytes[4] = 0;
    self->bytes[5] = 0;
    self->bytes[6] = 0;
    self->bytes[7] = 0;
    self->unk_50 = 0;
    self->unk_54 = 0;
    self->unk_58 = 0;
    self->unk_5C = -1;
    self->unk_64 = 0;
    func_0208e024(self->sub68);
    func_0208e024(self->sub84);
    func_0208e024(self->suba0);
    func_0208e024(self->subbc);
    {
        unsigned short *p = (unsigned short *) ((char *) self + 0x60);
        *p = 0;
        p = (unsigned short *) ((char *) self + 0x62);
        *p = 0;
    }
    return self;
}
