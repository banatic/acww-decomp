/* func_020a49bc @ 0x020a49bc, 0xe4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xa1];
    unsigned char state;
    unsigned char pad_A2[0x10e - 0xa1 - 1];
    union {
        struct {
            unsigned char low : 4;
            unsigned char high : 4;
        } bits;
        unsigned char byte;
    } flags;
} Func_020a49bc_Struct;

extern int func_02042324(void);
extern int func_020422f8(void);
extern int func_020a238c(void *);
extern int func_020a2120(Func_020a49bc_Struct *self, int nibble);
extern void func_020a261c(void);
extern void func_020a25cc(void);
extern void func_020a4e94(Func_020a49bc_Struct *self, int val);

void func_020a49bc(Func_020a49bc_Struct *self)
{
    switch (self->state) {
        case 0:
            self->state = 1;
            break;
        case 1:
            if (func_02042324()) {
                self->state = 2;
            } else {
                self->state = 3;
            }
            break;
        case 2:
            if (func_020422f8()) {
                self->state = 3;
            }
            break;
        case 3: {
            int r = func_020a238c(self);
            if (r == 1) {
                self->state = 6;
            } else if (r != 3) {
                self->state = 4;
            }
            break;
        }
        case 4: {
            int r = func_020a2120(self, self->flags.bits.high);
            if (r == 1) {
                self->state = 6;
            } else if (r == 0) {
                self->state = 5;
            }
            break;
        }
        case 5: {
            int r = func_020a2120(self, self->flags.bits.low);
            if (r == 1) {
                self->state = 6;
            } else if (r == 0) {
                self->state = 8;
            }
            break;
        }
        case 6:
            func_020a261c();
            self->state = 7;
            break;
        case 7:
            break;
        default:
            asm { add r0, self, #0 }
            func_020a25cc();
            func_020a4e94(self, 0x10);
            break;
    }
}
