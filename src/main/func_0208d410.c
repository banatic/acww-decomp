/* func_0208d410 @ 0x0208d410, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x50];
    int unk_50;
    int unk_54;
    int unk_58;
    int unk_5C;
} UnkStruct_0208d410;

extern int func_02039810(void);
extern int func_0208db3c(void *s);
extern void func_020e8bb0(void *a, int b, int c, int d, int e);

void func_0208d410(UnkStruct_0208d410 *self)
{
    int v1;
    int v2;
    int val;

    v1 = func_02039810();
    v2 = func_0208db3c(self);
    val = (v1 != 0 && v2 != 0) ? 0xfffec000 : 0;
    self->unk_58 += 0xa00;
    self->unk_58 = (self->unk_58 < 0x2300) ? 0x2300 : (self->unk_58 > 0x5000) ? 0x5000 : self->unk_58;
    if (val != self->unk_54) {
        if (self->unk_5C >= 0) {
            if (v2 != 0) {
                self->unk_5C++;
                if (self->unk_5C <= 0xa) {
                    goto l_done;
                }
            }
        }
        self->unk_54 = val;
        self->unk_5C = 0;
    l_done:;
    } else {
        self->unk_5C = 0;
    }
    func_020e8bb0((char *) self + 0x50, self->unk_54, 0x600, self->unk_58, 0x2300);
}
