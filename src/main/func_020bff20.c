/* func_020bff20 @ 0x020bff20, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020644cc(unsigned int size);
extern void func_020c0324(void *param, unsigned int a, unsigned int b, int flag);
extern void func_020bf220(void *param, unsigned int value, unsigned int cmd);

typedef struct {
    unsigned char pad_00[0x3c];
    unsigned int unk_3C;
    unsigned int unk_40;
    unsigned int unk_44;
    unsigned int unk_48;
    unsigned char pad_4C[0x04];
    unsigned int unk_50;
    unsigned char pad_54[0x18];
    unsigned int unk_6C;
    unsigned int unk_70;
} UnkStruct_020bff20;

void func_020bff20(UnkStruct_020bff20 *self, unsigned int flags)
{
    int r4;
    unsigned int r7, r0;
    unsigned int r1;

    switch ((flags >> 31) & 1) {
        default:
            r4 = 1;
            break;
        case 0:
            r4 = 0;
            break;
    }

    if (r4) {
        r7 = func_020644cc(0x60) + 0x50;
        if (((flags >> 28) & 1) != 0) {
            r0 = 0;
        } else {
            r0 = func_020644cc(0x20);
        }
        r0 += 0x52;
    } else {
        r7 = func_020644cc(0xa0) + 0x30;
        r0 = func_020644cc(0x60) + 0x32;
    }

    self->unk_6C = r7 << 12;
    self->unk_70 = 0x000bf000;
    self->unk_3C = r0 << 12;

    func_020c0324((char *) self + 0x34, self->unk_6C, self->unk_70, r4);

    self->unk_40 = 0;
    self->unk_44 = 0xffffc800;
    self->unk_48 = 0;
    self->unk_50 = 0x0000a000;

    r1 = (flags >> 8) & 3;
    if (r4) {
        r1 = 1;
    } else {
        r1 += 2;
    }
    func_020bf220(self, r1, 0x802);
}