/* func_0205bbac @ 0x0205bbac, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0205bbac {
    void *unk_00;
} UnkStruct_0205bbac;

extern char data_020dd3b8;
extern void func_0205bbdc(UnkStruct_0205bbac *self);

UnkStruct_0205bbac *func_0205bbac(UnkStruct_0205bbac *self)
{
    self->unk_00 = &data_020dd3b8;
    func_0205bbdc(self);
    return self;
}
