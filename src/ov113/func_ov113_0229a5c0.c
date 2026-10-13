/* func_ov113_0229a5c0 @ 0x0229a5c0, 0x98 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov113_02299d94(void *self, int a);
extern int func_ov113_02299da4(void *self, int a);
extern void RtcSendPxiCommand(int cmd);
extern void func_ov002_02207ecc(void *self, int a, int b, int c, int d);
extern void func_ov002_02207e80(void *self, int a, int b, int c);
extern void func_ov002_02208090(void *self, int a);

struct UnkStruct_0229a5c0 {
    unsigned char pad_00[0x9b];
    unsigned char mode_byte;
};

void func_ov113_0229a5c0(struct UnkStruct_0229a5c0 *self)
{
    int mode;

    func_ov113_02299d94(self, 0x100);

    switch (self->mode_byte) {
        case 1:
        case 4:
            mode = 2;
            break;
        case 0:
        case 5:
            mode = 3;
            break;
        default:
            mode = (func_ov113_02299da4(self, 0x40) != 0) ? 2 : 3;
            break;
    }

    switch (self->mode_byte) {
        case 0:
        case 1:
            RtcSendPxiCommand(0x3c);
            break;
        default:
            RtcSendPxiCommand(0x39);
            break;
    }

    func_ov002_02207ecc(self, 8, 0, mode, 0x30);
    func_ov002_02207e80(self, 2, 0, 0);
    func_ov002_02208090(self, 6);
}
