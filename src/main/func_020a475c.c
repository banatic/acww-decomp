/* func_020a475c @ 0x020a475c, 0xe4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020a475c UnkStruct_020a475c;
struct UnkStruct_020a475c {
    unsigned char pad_00[0xA1];
    unsigned char state;
    unsigned char pad_A2[0x6C];
    struct {
        unsigned char low : 4;
        unsigned char high : 4;
    } flags;
};

extern int func_020a259c(UnkStruct_020a475c *self, int arg2);
extern int func_020a238c(UnkStruct_020a475c *self);
extern int func_020a2120(UnkStruct_020a475c *self, int value);
extern void func_020a261c(UnkStruct_020a475c *self);
extern void func_020a25cc(UnkStruct_020a475c *self);
extern void func_020a4e94(UnkStruct_020a475c *self, int arg2);

void func_020a475c(UnkStruct_020a475c *self)
{
    switch (self->state) {
        case 0:
            if (func_020a259c(self, 0) != 0) {
                self->state = 1;
            }
            break;
        case 1: {
            int r = func_020a238c(self);
            if (r == 1) {
                self->state = 5;
            } else if (r == 3) {
                break;
            } else {
                self->state = 2;
            }
            break;
        }
        case 2: {
            int r = func_020a2120(self, self->flags.high);
            if (r == 1) {
                self->state = 5;
            } else if (r == 0) {
                self->state = 3;
            }
            break;
        }
        case 3: {
            int r = func_020a2120(self, self->flags.low);
            if (r == 1) {
                self->state = 5;
            } else if (r == 0) {
                self->state = 4;
            }
            break;
        }
        case 4: {
            int r = func_020a2120(self, 2);
            if (r == 1) {
                self->state = 5;
            } else if (r == 0) {
                self->state = 7;
            }
            break;
        }
        case 5:
            func_020a261c(self);
            self->state = 6;
            break;
        case 6:
            break;
        default:
            func_020a25cc(self);
            func_020a4e94(self, 0xC);
            break;
    }
}
