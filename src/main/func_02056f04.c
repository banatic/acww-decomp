/* func_02056f04 @ 0x02056f04, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020dd174;
extern void *MI_CpuFill8(void *s, int c, unsigned int n);

typedef struct {
    void *data;        // 0x00
    char buffer[0x24]; // 0x04
    char pad_28[12];   // 0x28
    int unk_34;        // 0x34
    int unk_38;        // 0x38
} UnkStruct_02056f04;

UnkStruct_02056f04 *func_02056f04(UnkStruct_02056f04 *self)
{
    self->data = (void *) &data_020dd174;
    MI_CpuFill8(self->buffer, 0, 0x24);
    self->unk_34 = 0;
    self->unk_38 = 0;
    return self;
}
