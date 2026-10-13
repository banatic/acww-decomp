/* func_ov099_0229c4fc @ 0x0229c4fc, 0x24 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x290b];
    unsigned char flag;
} UnkStruct_0229c4fc;

extern void func_ov099_0229c5a8(UnkStruct_0229c4fc *self);
extern void func_ov099_0229d0f0(UnkStruct_0229c4fc *self);

void func_ov099_0229c4fc(UnkStruct_0229c4fc *self)
{
    switch (self->flag) {
        case 0:
            func_ov099_0229c5a8(self);
            break;
        case 1:
        default:
            func_ov099_0229d0f0(self);
            break;
    }
}
