/* func_0208b658 @ 0x0208b658, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0208b658 {
    char pad_00[0x28];
    unsigned int unk_28;
    unsigned int unk_2C;
    int unk_30;
    int unk_34;
};

extern int func_0206fd04(void);
extern int func_02039860(void);
extern int func_020e8bb0(void *a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern void func_0208b648(struct UnkStruct_0208b658 *s);

void func_0208b658(struct UnkStruct_0208b658 *self)
{
    unsigned int val;

    if (func_0206fd04() != 0) {
        if (func_02039860() != 0) {
            val = 0x28000;
        } else {
            val = 0;
        }
        self->unk_30 += 0xa00;
        self->unk_30 = (self->unk_30 < 0x2300) ? 0x2300 : (self->unk_30 > 0x5000) ? 0x5000 : self->unk_30;
        if (val != self->unk_2C) {
            if (self->unk_34 >= 0) {
                self->unk_34++;
                if (self->unk_34 <= 5) {
                    goto l_done;
                }
            }
            self->unk_2C = val;
            self->unk_34 = 0;
        l_done:;
        } else {
            self->unk_34 = 0;
        }
        func_020e8bb0((char *) self + 0x28, self->unk_2C, 0x600, self->unk_30, 0x2300);
    } else {
        func_0208b648(self);
    }
}
