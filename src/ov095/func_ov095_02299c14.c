/* func_ov095_02299c14 @ 0x02299c14, 0xe4 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x16];
    unsigned char unk_16;
    unsigned char pad_17[0x11];
    unsigned int state;
    unsigned char pad_2C[0x16];
    unsigned char unk_42;
} UnkStruct_02299c14;

extern int func_ov002_022088cc(void *);
extern int func_ov002_022088ac(void *);
extern int func_ov002_0220889c(void *);

int func_ov095_02299c14(UnkStruct_02299c14 *self, void *arg)
{
    unsigned int st = self->state;
    if (st == 0x107) {
        if (func_ov002_022088cc(arg)) {
            switch (self->unk_16) {
                case 0:
                    self->state = 0x2c;
                    break;
                case 1:
                    self->state = 0x6e;
                    break;
                case 2:
                    self->state = 0x90;
                    break;
                case 3:
                    self->state = 0xc8;
                    break;
                case 4:
                    self->state = 0xf6;
                    break;
            }
        } else if (self->unk_42 == 5 && func_ov002_022088ac(arg)) {
            self->state = 0x108;
        }
        return 1;
    } else if (st == 0x108) {
        if (func_ov002_022088cc(arg)) {
            switch (self->unk_16) {
                case 0:
                    self->state = 0x18;
                    break;
                case 1:
                    self->state = 0x6b;
                    break;
                case 2:
                    self->state = 0x91;
                    break;
                case 3:
                    self->state = 0xc3;
                    break;
                case 4:
                    self->state = 0xf4;
                    break;
            }
        } else if (func_ov002_0220889c(arg)) {
            self->state = 0x107;
        }
        return 1;
    }
    return 0;
}
