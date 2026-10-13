/* func_ov111_0229f524 @ 0x0229f524, 0x30 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229f524 {
    unsigned char pad_00[0x9C];
    unsigned char unk_9C;
    unsigned char pad_9D[1];
    unsigned char unk_9E;
    unsigned char pad_9F[2];
    unsigned char unk_A1;
    unsigned char pad_A2[0x3C74];
    unsigned char big_field;
} UnkStruct_0229f524;

extern unsigned char func_02051d08(void *ptr, unsigned char byte);
extern void func_ov111_0229efec(UnkStruct_0229f524 *self);

void func_ov111_0229f524(UnkStruct_0229f524 *self)
{
    unsigned char result;
    result = func_02051d08(&self->big_field, self->unk_9E);
    self->unk_A1 = result;
    self->unk_9C = 0x10;
    func_ov111_0229efec(self);
}
