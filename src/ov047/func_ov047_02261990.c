/* func_ov047_02261990 @ 0x02261990, 0x24 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *unk_00;
    unsigned char pad_04[0xce - 4];
    unsigned short unk_CE;
} UnkStruct_02261990;

void *func_0202eb70(void *self);
extern int data_ov047_02262c14;

UnkStruct_02261990 *func_ov047_02261990(UnkStruct_02261990 *self)
{
    func_0202eb70(self);
    self->unk_00 = &data_ov047_02262c14;
    self->unk_CE = 0xfff1;
    return self;
}
