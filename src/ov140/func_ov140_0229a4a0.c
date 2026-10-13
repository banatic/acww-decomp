/* func_ov140_0229a4a0 @ 0x0229a4a0, 0xa4 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022088cc(void *);
extern int func_ov002_022088bc(void *);
extern int func_ov002_022088ac(void *);
extern int func_ov002_0220889c(void *);

typedef struct {
    unsigned char pad_00[0x8dc];
    unsigned char state;
} UnkStruct_0229a4a0;

int func_ov140_0229a4a0(UnkStruct_0229a4a0 *self, void *arg)
{
    unsigned char cur = self->state;

    if (cur <= 5) {
        if (func_ov002_022088cc(arg)) {
            if (self->state != 0) {
                self->state--;
            }
        } else if (func_ov002_022088bc(arg)) {
            if (self->state < 5) {
                self->state++;
            } else {
                self->state = 6;
            }
        }
    } else {
        if (func_ov002_022088cc(arg)) {
            self->state = 5;
        } else if (func_ov002_022088ac(arg)) {
            if (self->state > 6) {
                self->state--;
            }
        } else if (func_ov002_0220889c(arg)) {
            if (self->state < 8) {
                self->state++;
            }
        }
    }

    return cur != self->state;
}
