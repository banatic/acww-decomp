/* func_ov101_0229c970 @ 0x0229c970, 0x66 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

struct Game {
    char pad_00[0xac];
    unsigned short unk_AC;
    unsigned char unk_AE;
    unsigned char unk_AF;
    char pad_B0[0x44];
    char unk_F4;
};

extern int func_ov101_0229ce38(struct Game *self, void *other);
extern void *func_ov101_0229ce1c(struct Game *self, void *other);
extern int func_ov094_0229aaac(char *ptr, void *p);
extern int func_ov094_0229aa84(char *ptr, void *p);
extern void func_ov094_0229aa58(char *ptr, void *p);
extern void func_ov094_0229a99c(char *ptr, int a, int b);

void func_ov101_0229c970(struct Game *self, void *other)
{
    if (func_ov101_0229ce38(self, other)) {
        void *p = func_ov101_0229ce1c(self, other);
        self->unk_AF = 1;
        self->unk_AC = (unsigned short) func_ov094_0229aaac(&self->unk_F4, p);
        self->unk_AE = (unsigned char) func_ov094_0229aa84(&self->unk_F4, p);
        func_ov094_0229aa58(&self->unk_F4, p);
        func_ov094_0229a99c(&self->unk_F4, self->unk_AC, self->unk_AE);
    }
}
