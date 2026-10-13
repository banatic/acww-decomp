/* func_ov003_022103cc @ 0x022103cc, 0xa8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02008258(void *a, unsigned int b);
extern void func_ov003_02210660(void *a, unsigned char *b);
extern int func_02096518(unsigned int *a, int b, unsigned int c);
extern void func_ov003_0221066c(void *a, int b, int c);
extern void func_ov003_02210668(void *a, int b);
extern void func_0209129c(int a, int b);
extern int func_02056f94(void *a);
extern void func_0200d4e8(void *a, int b, int c, int d);

typedef struct {
    unsigned char pad_00[0x2d0];
    unsigned char pad_2D0[0x504];
    int unk_7D4;
    unsigned char pad_7D8[0x18];
    unsigned int unk_7F0;
    unsigned char pad_7F4[0x8];
    unsigned int unk_7FC;
    unsigned int unk_800;
    unsigned char pad_804[0xec];
} UnkStruct_022103cc;

void func_ov003_022103cc(UnkStruct_022103cc *self)
{
    unsigned char flag;
    unsigned int local;
    int *p;
    char *base;

    self->unk_7FC = func_02008258(self, self->unk_7F0);

    base = (char *) self + 0x8f0;
    func_ov003_02210660(base, &flag);

    if (flag && func_02096518(&local, -1, self->unk_800) && local == 0x63) {
        func_ov003_0221066c(self, 6, -1);
        p = (int *) ((char *) self + 0x7d4);
        func_ov003_02210668(base, 1);
        if (self->unk_7D4 != -1) {
            func_0209129c(self->unk_7D4, -1);
            *p = -1;
        }
    } else {
        if (func_02056f94((char *) self + 0x2d0)) {
            func_0200d4e8(self, 3, 1, -1);
        }
    }
}
