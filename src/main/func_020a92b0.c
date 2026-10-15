/* func_020a92b0 @ 0x020a92b0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0x20];
    int unk_24;
    unsigned char unk_28;
} UnkStruct_020a92b0;

extern void *func_020a9484(UnkStruct_020a92b0 *self);

extern unsigned char data_020e3de4[];

UnkStruct_020a92b0 *func_020a92b0(UnkStruct_020a92b0 *self, char value)
{
    func_020a9484(self);
    self->unk_00 = (unsigned int) data_020e3de4;
    self->unk_24 = 0;
    self->unk_28 = value;
    return self;
}
