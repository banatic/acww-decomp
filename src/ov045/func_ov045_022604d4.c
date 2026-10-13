/* func_ov045_022604d4 @ 0x022604d4, 0x20 bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8c38(void *self);
extern void func_020edb3c(void *self);

typedef struct {
    unsigned int unk_00;
} UnkStruct_022604d4;

extern unsigned char data_ov045_02261414[];

void *func_ov045_022604d4(UnkStruct_022604d4 *self)
{
    self->unk_00 = (unsigned int) data_ov045_02261414;
    func_020a8c38(self);
    func_020edb3c(self);
    return self;
}
