/* mole_talk_3: 2 functions, module ov077
 * mwccarm 1.2/base -O4,s
 * func_ov077_02278e10 @ 0x02278e10, 0xe bytes, Thumb
 * func_ov077_02278dd4 @ 0x02278dd4, 0x3c bytes, Thumb
 */

struct UnkStruct_02278e10 {
    char pad_00[0xb0];
    int unk_B0;
    char unk_B4;
};

extern int func_020e8858(void *);
extern void func_0206844c(int, char *, int);
extern int func_020155cc(void *);
extern int data_ov077_02279700;

void func_ov077_02278e10(struct UnkStruct_02278e10 *self, int value)
{
    self->unk_B0 = value;
    self->unk_B4 = 0x5a;
}

void func_ov077_02278dd4(char *this)
{
    char c;

    if (func_020e8858((char *) this + 0xb4) == 0) {
        c = 0x10;
        func_0206844c(*(int *) ((char *) this + 0x40), &c, data_ov077_02279700);
        func_020155cc(this);
        func_ov077_02278e10((struct UnkStruct_02278e10 *) this, 0);
    }
}
