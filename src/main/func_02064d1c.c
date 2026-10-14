/* func_02064d1c @ 0x02064d1c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *unk_00;
    unsigned char pad_04[0x54];
} UnkStruct_02064d1c;

extern char data_020de710;
extern char data_020da13c;
extern void func_02064d8c(void *obj);
extern void __cxa_vec_cleanup(void *dest, int count, int size, void (*constructor)(void *));
extern void func_020ee62c(UnkStruct_02064d1c *self);

UnkStruct_02064d1c *func_02064d1c(UnkStruct_02064d1c *self)
{
    self->unk_00 = &data_020de710;
    __cxa_vec_cleanup((char *) self + 0x58, 3, 0x44, func_02064d8c);
    self->unk_00 = &data_020da13c;
    func_020ee62c(self);
    return self;
}
