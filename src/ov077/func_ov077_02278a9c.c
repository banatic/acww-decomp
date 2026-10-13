/* func_ov077_02278a9c @ 0x02278a9c, 0xb8 bytes, Thumb, module ov077
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02278a9c UnkStruct_02278a9c;
struct UnkStruct_02278a9c {
    unsigned char pad_00[0x1e];
    unsigned char cmd;
    unsigned char pad_1F[0x40 - 0x1f];
    unsigned int unk_40;
};

extern void *func_020160b4(UnkStruct_02278a9c *self);
extern int func_020ab504(void *p);
extern int func_020ab4f8(void *p);
extern int func_020644cc(int x);
extern int func_020e8b0c(int a, int b, int c);
extern void func_0206844c(unsigned int a, void *b, unsigned int c);
extern unsigned int data_ov077_02279700;

void func_ov077_02278a9c(UnkStruct_02278a9c *self)
{
    int chk;
    unsigned char out;
    unsigned char cmd;

    chk = func_020ab504(func_020160b4(self));
    out = 0xff;
    cmd = self->cmd;

    switch (cmd) {
        case 0xb:
            if (chk == 0) {
                out = (func_020644cc(2) == 0) ? 0xe : 0xd;
            } else {
                out = (func_020644cc(2) == 0) ? 0xe : 0xc;
            }
            break;
        case 0x1f:
        case 0x20:
        case 0x21: {
            int r = func_020644cc(0xd);
            int x = func_020ab4f8(func_020160b4(self));
            if (func_020e8b0c(x, r, r + 5) != 0) {
                out = 0x22;
            } else {
                out = (func_020644cc(2) == 0) ? 0x20 : 0x21;
            }
            break;
        }
        default:
            break;
    }

    if (out != 0xff) {
        unsigned char buf = out;
        func_0206844c(self->unk_40, &buf, data_ov077_02279700);
    }
}
