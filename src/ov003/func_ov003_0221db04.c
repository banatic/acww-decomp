/* func_ov003_0221db04 @ 0x0221db04, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov003_022390e8;
extern char data_ov003_022391ac;
extern void *func_ov009_0226539c(void *self);
extern void func_020edf54(void *self);

typedef struct {
    void *unk_00;
    unsigned char pad_04[0xe8];
    void *unk_EC;
} UnkStruct_0221db04;

UnkStruct_0221db04 *func_ov003_0221db04(UnkStruct_0221db04 *self)
{
    self->unk_00 = &data_ov003_022390e8;
    self->unk_EC = &data_ov003_022391ac;
    func_ov009_0226539c(self);
    func_020edf54(self);
    return self;
}
