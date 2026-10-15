/* func_0206d5e4 @ 0x0206d5e4, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020def7c;
void *func_020a92b0(void *self, int flag);
void func_020a8754(void *sub);
void *func_020a9034(int a, int b, int c);
void func_020a8eec(void *ptr, void *self);

typedef struct {
    void *unk_00;
    char pad_04[0x28];
    int unk_2C;
    void *unk_30;
    char sub_34[0x14];
    int unk_48;
    int unk_4C;
    int unk_50;
} UnkStruct_0206d5e4;

void *func_0206d5e4(UnkStruct_0206d5e4 *self, int value)
{
    func_020a92b0(self, 1);
    self->unk_00 = &data_020def7c;
    self->unk_2C = value;
    self->unk_30 = 0;
    func_020a8754(self->sub_34);
    self->unk_48 = 0;
    self->unk_4C = 0;
    self->unk_50 = 0;
    self->unk_30 = func_020a9034(0, 20, 2);
    if (self->unk_30 != 0) {
        func_020a8eec(self->unk_30, self);
    }
    return self;
}
