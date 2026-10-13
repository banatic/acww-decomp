/* func_020a9464 @ 0x020a9464, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a94a4(void *);
extern void func_020a9c98(void *);

struct UnkStruct_020a9464 {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
};

extern unsigned char data_020e3e24[];

struct UnkStruct_020a9464 *func_020a9464(struct UnkStruct_020a9464 *self)
{
    self->unk_00 = (unsigned int) data_020e3e24;
    func_020a94a4(self);
    func_020a9c98(&self->unk_08);
    return self;
}
