/* func_ov121_0229bcc8 @ 0x0229bcc8, 0xb4 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f58c(void);
extern int func_0206f56c(void);
extern int func_0206fe60(void);
extern int func_ov090_022990e0(void);
extern int func_ov121_0229bc70(void *self, int value);

typedef struct {
    unsigned char pad[0x8d];
    unsigned char byte;
} UnkStruct_0229bcc8;

extern struct {
    unsigned char pad[2];
    unsigned short flags;
} data_021fbe40;

int func_ov121_0229bcc8(UnkStruct_0229bcc8 *self)
{
    int r5;

    func_0206f58c();
    if (func_0206f56c()) {
        switch (self->byte) {
            case 0:
            case 1:
            case 4:
            case 7:
            case 8:
                return func_ov121_0229bc70(self, 7);
            default:
                break;
        }
    }

    if (self->byte != 0 && self->byte != 4) {
        return 0;
    }

    r5 = -1;
    if (func_0206fe60()) {
        r5 = func_ov090_022990e0();
    } else {
        unsigned short w = data_021fbe40.flags;
        if (w & 0x800) {
            r5 = 0;
        } else if (w & 0x400) {
            r5 = 5;
        } else if (w & 0x4) {
            r5 = 4;
        }
    }

    return func_ov121_0229bc70(self, r5);
}
