/* func_ov122_0229f940 @ 0x0229f940, 0x18 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229f940 {
    char pad_00[0xad];
    unsigned char unk_AD;
    unsigned char unk_AE;
};
extern void func_ov122_0229efc8(void *, int);
void func_ov122_0229f940(struct UnkStruct_0229f940 *self)
{
    self->unk_AD = 0;
    self->unk_AE = 0;
    func_ov122_0229efc8(self, 8);
}
