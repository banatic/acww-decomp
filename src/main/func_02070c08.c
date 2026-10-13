/* func_02070c08 @ 0x02070c08, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02070c08 {
    void *unk_00;
    char pad_04[0x64];
    int unk_68;
} UnkStruct_02070c08;

extern void func_020a8cac(UnkStruct_02070c08 *self);
extern void func_020a8c1c(UnkStruct_02070c08 *self);
extern char data_020e179c;

UnkStruct_02070c08 *func_02070c08(UnkStruct_02070c08 *self)
{
    func_020a8cac(self);
    self->unk_00 = &data_020e179c;
    func_020a8c1c(self);
    self->unk_68 = 0;
    return self;
}
