/* func_ov121_0229b020 @ 0x0229b020, 0x58 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_020431c8(int);
extern void func_020431b8(int);
extern void func_ov121_0229a50c(void *);
extern void func_ov121_02299c88(void *, unsigned char);
extern void func_ov121_0229afb8(void *);
extern void func_ov121_0229af7c(void *, int, int);
extern void RtcSendPxiCommand(int);

typedef struct {
    unsigned char pad_00[0x98];
    int state;
    unsigned char pad_9C[0x13];
    unsigned char unk_AF;
} UnkStruct_0229b020;

void func_ov121_0229b020(UnkStruct_0229b020 *self)
{
    int result = func_020431c8(self->state);
    switch (result) {
        case 1:
            func_ov121_0229a50c(self);
            func_ov121_02299c88(self, self->unk_AF);
            func_ov121_0229afb8(self);
            break;
        case 2:
            func_ov121_0229af7c(self, 3, 0);
            RtcSendPxiCommand(0x73);
            break;
        default:
            return;
    }
    func_020431b8(self->state);
    self->state = -1;
}
