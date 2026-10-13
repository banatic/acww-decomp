/* func_ov076_02278af0 @ 0x02278af0, 0x88 bytes, Thumb, module ov076
 * mwccarm 1.2/base -O4,s
 */

extern int func_020160b4(void *self);
extern int func_020ab504(int a);
extern int func_020644cc(int arg);
extern void func_0206844c(void *a, void *b, void *c);
extern char data_ov076_022796e0;

struct UnkStruct_ov076_02278af0 {
    unsigned char pad_00[0x1e];
    unsigned char unk_1E;
    unsigned char pad_1F[0x40 - 0x1f];
    void *unk_40;
};

void func_ov076_02278af0(struct UnkStruct_ov076_02278af0 *self)
{
    int a;
    int b;
    void *p;
    unsigned char message;
    char msg;

    a = func_020160b4(self);
    b = func_020ab504(a);
    p = &data_ov076_022796e0;
    message = 0xff;

    switch (self->unk_1E) {
        case 0:
        case 1:
            if (b == 0) {
                message = (unsigned char) (func_020644cc(0xee) + 0xf);
            } else {
                message = 5;
            }
            break;
        case 2:
            if (b == 2) {
                message = 4;
            }
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            break;
        case 8:
            if (b == 0) {
                message = 0xb;
            } else if (b == 1) {
                message = 9;
            } else {
                message = 0xa;
            }
            break;
        default:
            break;
    }

    if (message != 0xff) {
        msg = (char) message;
        func_0206844c(self->unk_40, &msg, p);
    }
}
