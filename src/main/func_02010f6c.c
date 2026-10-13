/* func_02010f6c @ 0x02010f6c, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200e9a8(void *a, unsigned char *b, unsigned int *c, unsigned int *d, short *e);
extern int func_020b65c4(void);
extern int func_020113bc(short *a, short b);
extern int func_020110a0(void *a, short *b);
extern int func_02011490(unsigned int *a, unsigned int b);

struct UnkStruct_02010f6c {
    char pad_00[0x5c];
    unsigned int sub1;
    char pad_60[4];
    unsigned int sub2;
    char pad_68[0x26];
    short unk_8E;
};

int func_02010f6c(struct UnkStruct_02010f6c *self)
{
    unsigned char b;
    short s6, s8;
    unsigned int v1, v2;
    int ok;

    if (func_0200e9a8(self, &b, &v1, &v2, &s6) == 0) {
        return 0;
    }

    if (b != func_020b65c4()) {
        return 0;
    }

    s8 = self->unk_8E;

    ok = (func_020113bc(&s8, s6) == 0);

    func_020110a0(self, &s8);
    func_02011490(&self->sub1, v1);
    func_02011490(&self->sub2, v2);

    if (ok) {
        ok = (v1 == self->sub1 && v2 == self->sub2);
    }

    return ok;
}
