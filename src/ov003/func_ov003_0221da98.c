/* func_ov003_0221da98 @ 0x0221da98, 0x6c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct SELF {
    unsigned char pad_00[0x198];
    void *unk_198;
    unsigned char pad_19C[0x2b4 - 0x19c];
    signed char unk_2B4;
    signed char unk_2B5;
};

extern int func_0205790c(void *, const char *);
extern void func_02055de0(void *, void (*)(void *), int, int, void *, int);
extern void func_ov003_0221db90(void *state);
extern const char data_ov003_02239224[];
extern const char data_ov003_0223922c[];

int func_ov003_0221da98(struct SELF *self)
{
    self->unk_2B4 = func_0205790c(self->unk_198, data_ov003_02239224);
    self->unk_2B5 = func_0205790c(self->unk_198, data_ov003_0223922c);
    if (self->unk_2B4 != -1 && self->unk_2B5 != -1) {
        func_02055de0((char *) self + 0x13c, func_ov003_0221db90, 6, 2, self, 0);
    }
    return 1;
}
