/* func_020b4044 @ 0x020b4044, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020b4044 {
    void *unk_00;
    char pad_04[0x1c];
    int unk_20;
    int unk_24;
    char unk_28;
    char unk_29;
};

extern void *func_020a81b8(void *param);

extern unsigned char data_020e5200[];

struct UnkStruct_020b4044 *func_020b4044(struct UnkStruct_020b4044 *self)
{
    func_020a81b8(self);
    self->unk_00 = (void *) data_020e5200;
    self->unk_20 = 0;
    self->unk_24 = 0;
    self->unk_28 = 0;
    self->unk_29 = 0;
    return self;
}
