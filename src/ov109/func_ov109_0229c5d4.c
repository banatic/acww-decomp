/* func_ov109_0229c5d4 @ 0x0229c5d4, 0x64 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov109_0229ca7c(void *self, unsigned char byte);
extern int func_02060a34(unsigned int arg0);
extern void func_ov109_0229cccc(void *self, int num);
extern void func_020609dc(int result);
extern void func_ov109_0229cc0c(void *self, unsigned char byte, int constant, int zero);
extern void func_ov109_0229c4f4(void *self);
extern void func_ov109_0229cd9c(void *self);

struct UnkStruct_0229c5d4 {
    char pad_00[0x29d4];
    unsigned char unk_29D4;
    char pad_29D5[2];
    unsigned char unk_29D7;
};

void func_ov109_0229c5d4(struct UnkStruct_0229c5d4 *self)
{
    switch (self->unk_29D7) {
        case 0: {
            int result;
            result = func_ov109_0229ca7c(self, self->unk_29D4);
            if (func_02060a34(result) != 0) {
                func_ov109_0229cccc(self, 17);
            } else {
                func_020609dc(result);
                func_ov109_0229cc0c(self, self->unk_29D4, 0xfff1, 0);
                func_ov109_0229c4f4(self);
            }
            break;
        }
        case 1:
        default:
            func_ov109_0229cd9c(self);
            break;
    }
}
