/* func_ov003_0221e908 @ 0x0221e908, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov003_0223948c;
extern char data_ov003_02239550;

typedef struct UnkStruct_0221e908 {
    void *unk_00;
    char pad_04[0xe8];
    void *unk_EC;
    char pad_F0[0x1c8];
    char area_2b8;
    char pad_2B9[0x1f];
    char area_2d8;
} UnkStruct_0221e908;

extern int func_020b7f60(void *);
extern void *func_020565b0(void *);
extern void *func_ov009_0226539c(UnkStruct_0221e908 *);

UnkStruct_0221e908 *func_ov003_0221e908(UnkStruct_0221e908 *self)
{
    self->unk_00 = &data_ov003_0223948c;
    self->unk_EC = &data_ov003_02239550;
    func_020b7f60(&self->area_2d8);
    func_020565b0(&self->area_2b8);
    func_ov009_0226539c(self);
    return self;
}
