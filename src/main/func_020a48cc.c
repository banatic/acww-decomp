/* func_020a48cc @ 0x020a48cc, 0xd2 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xa1];
    unsigned char state;
} StateStruct;

extern int func_020a259c(StateStruct *self, int a);
extern int func_020a1628(void);
extern int func_020a1cec(StateStruct *self, int a);
extern void func_020a261c(void);
extern void func_020a25cc(void);
extern void func_020a4e94(StateStruct *self, int a);

void func_020a48cc(StateStruct *self)
{
    switch (self->state) {
        case 0:
            if (func_020a259c(self, 0) != 0) {
                self->state = 1;
            }
            break;
        case 1: {
            int r = func_020a1628();
            if (r == 1) {
                self->state = 5;
            } else if (r == 0) {
                self->state = 2;
            }
            break;
        }
        case 2: {
            int r = func_020a1cec(self, 0);
            if (r == 1) {
                self->state = 5;
            } else if (r == 0) {
                self->state = 3;
            }
            break;
        }
        case 3: {
            int r = func_020a1cec(self, 1);
            if (r == 1) {
                self->state = 5;
            } else if (r == 0) {
                self->state = 4;
            }
            break;
        }
        case 4: {
            int r = func_020a1cec(self, 2);
            if (r == 1) {
                self->state = 5;
            } else if (r == 0) {
                self->state = 7;
            }
            break;
        }
        case 5:
            func_020a261c();
            self->state = 6;
            break;
        default:
            asm { add r0, self, #0 }
            func_020a25cc();
            func_020a4e94(self, 0xc);
            break;
        case 6:
            break;
    }
}
