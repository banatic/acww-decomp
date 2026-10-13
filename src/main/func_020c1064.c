/* func_020c1064 @ 0x020c1064, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020eabc8(void *, int);
extern void VEC_Add(void *, void *, void *);
extern int func_0208a160(void *);
extern int func_020c1144(void *);
extern int data_020d26f0[];

struct UnkStruct_020c1064 {
    int unk_00;
    int unk_04;
    char pad_08[8];
    int unk_10;
    char pad_14[32];
    int unk_34;
    int unk_38;
    int unk_3C;
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4C;
    int unk_50;
    unsigned short unk_54;
    char pad_56[10];
    unsigned int unk_60;
    int unk_64;
};

void func_020c1064(struct UnkStruct_020c1064 *self)
{
    unsigned int state;
    int count;
    int val;

    state = self->unk_60 & 0xf;
    self->unk_64++;

    if (state == 0) {
        func_020eabc8(&self->unk_40, 0xe66);
        VEC_Add(&self->unk_34, &self->unk_40, &self->unk_34);
        if (func_0208a160(&self->unk_10) != 0) {
            self->unk_04 = 3;
        }
    } else if (state == 1) {
        count = self->unk_64;
        val = data_020d26f0[count];
        if (count >= 23) {
            self->unk_04 = 3;
        } else {
            self->unk_4C = val;
            self->unk_50 = val;
            self->unk_54 += 0xe39;
            if (func_020c1144(self) == 0) {
                self->unk_04 = 3;
            }
        }
    } else {
        if (self->unk_64 >= 6) {
            self->unk_04 = 3;
        }
    }
}
