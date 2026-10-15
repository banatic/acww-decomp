/* func_020a467c @ 0x020a467c, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a259c(void *s, int a);
extern int func_020a238c(void *s);
extern int func_020a2120(void *s, int a);
extern void func_020a261c(void *object);
extern void func_020a25cc(void *receiver);
extern void func_020a4e94(void *s, int a);

struct UnkStruct_020a467c {
    unsigned char pad_00[0xa1];
    unsigned char state;
    unsigned char pad_A2[0x6c];
    unsigned char low : 4;
    unsigned char high : 4;
};

void func_020a467c(struct UnkStruct_020a467c *self)
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
                self->state = 4;
            } else if (r != 3) {
                self->state = 2;
            }
            break;
        }
        case 2: {
            int r = func_020a2120(self, self->high);
            if (r == 1) {
                self->state = 4;
            } else if (r == 0) {
                self->state = 3;
            }
            break;
        }
        case 3: {
            int r = func_020a2120(self, self->low);
            if (r == 1) {
                self->state = 4;
            } else if (r == 0) {
                self->state = 6;
            }
            break;
        }
        case 4:
            func_020a261c(self);
            self->state = 5;
            break;
        case 5:
            break;
        default:
            func_020a25cc(self);
            func_020a4e94(self, 0xf);
            break;
    }
}
