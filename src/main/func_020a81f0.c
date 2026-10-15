/* func_020a81f0 @ 0x020a81f0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e3d64;
extern void *func_020a8c38(void *);
extern void func_020edb3c(void *);

struct UnkStruct_020a81f0 {
    char *unk_00;
};

struct UnkStruct_020a81f0 *func_020a81f0(struct UnkStruct_020a81f0 *self)
{
    self->unk_00 = &data_020e3d64;
    func_020a8c38(self);
    func_020edb3c(self);
    return self;
}
