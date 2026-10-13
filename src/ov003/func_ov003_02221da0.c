/* func_ov003_02221da0 @ 0x02221da0, 0x30 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02221da0;
extern void func_0204f794(void *addr, unsigned int a, unsigned int b);
extern void func_ov003_02222aa4(struct UnkStruct_02221da0 *self);

typedef struct UnkStruct_02221da0_2 {
    unsigned int unk_00;
    unsigned int unk_04;
} UnkStruct_02221da0_2;

struct UnkStruct_02221da0 {
    unsigned char pad_00[0x30];
    unsigned int arr[6];
};

void func_ov003_02221da0(struct UnkStruct_02221da0 *self, const UnkStruct_02221da0_2 *data)
{
    func_0204f794((char *) self + 0x18, data->unk_00, data->unk_04);
    self->arr[3] = 0x1000;
    self->arr[4] = 0x1000;
    self->arr[5] = 0x1000;
    self->arr[0] = 0;
    self->arr[1] = 0;
    self->arr[2] = 0;
    func_ov003_02222aa4(self);
}
