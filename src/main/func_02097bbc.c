/* func_02097bbc @ 0x02097bbc, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *);

struct UnkStruct_02097bbc {
    volatile unsigned int unk_00;
};

extern unsigned char data_020da13c[];
extern unsigned char data_020e30b8[];

void *func_02097bbc(struct UnkStruct_02097bbc *self)
{
    self->unk_00 = (unsigned int) data_020e30b8;
    self->unk_00 = (unsigned int) data_020da13c;
    func_020ee62c(self);
    return self;
}
