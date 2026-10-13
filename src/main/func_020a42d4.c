/* func_020a42d4 @ 0x020a42d4, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a238c(void *);
extern int func_020a2120(void *, int);
extern void func_020a4e94(void *, int);

typedef struct {
    unsigned char pad_00[0xa1];
    unsigned char state;
    unsigned char pad_A2[0x6c];
    unsigned char unk_10E;
} StateStruct;

void func_020a42d4(StateStruct *self)
{
    switch (self->state) {
        case 0: {
            int r = func_020a238c(self);
            if (r == 1) {
                self->state = 3;
                break;
            }
            if (r == 3) {
                return;
            }
            self->state = 1;
            break;
        }
        case 1: {
            int r = func_020a2120(self, ((unsigned int) self->unk_10E << 24) >> 28);
            if (r == 1) {
                self->state = 3;
                break;
            }
            if (r == 0) {
                self->state = 2;
                break;
            }
            return;
        }
        case 2: {
            int r = func_020a2120(self, 2);
            if (r == 1) {
                self->state = 3;
                break;
            }
            if (r == 0) {
                self->state = 4;
                break;
            }
            return;
        }
        case 3:
            break;
        default:
            func_020a4e94(self, 0);
            break;
    }
}
