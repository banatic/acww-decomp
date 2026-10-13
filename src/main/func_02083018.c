/* func_02083018 @ 0x02083018, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *unk_00;
} UnkStruct_02083018;

extern void func_020830d0(UnkStruct_02083018 *, void *);
extern void func_020edb3c(UnkStruct_02083018 *);
extern char data_020e1a18;

UnkStruct_02083018 *func_02083018(UnkStruct_02083018 *self)
{
    self->unk_00 = &data_020e1a18;
    func_020830d0(self, &data_020e1a18);
    func_020edb3c(self);
    return self;
}
