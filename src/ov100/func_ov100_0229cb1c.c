/* func_ov100_0229cb1c @ 0x0229cb1c, 0x64 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208e4c0(void *, int);
extern int func_ov002_022090e4(void *, int);
extern int func_ov002_02208ae4(void *);
extern int func_ov002_02208ad8(void *, int);
extern void func_ov002_0220a0b4(void *, int, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

typedef struct {
    char pad_00[0x2925];
    unsigned char unk_2925;
    unsigned char unk_2926;
} TestStruct;

void func_ov100_0229cb1c(TestStruct *self)
{
    char *base = (char *) self;
    int tmp1, tmp2;

    self->unk_2925 = 1;
    self->unk_2926 = (unsigned char) func_ov002_022090e4(base + 0x22d8, 1);
    tmp1 = func_ov002_02208ae4(base + 0x22d8);
    tmp2 = func_ov002_02208ad8(base + 0x22d8, self->unk_2926);
    func_ov002_0220a0b4(base + 0x2274, tmp1, tmp2);
    func_0208e4c0(base + 0x2274, 8);
    func_ov002_02208098((void *) (base), 0x12);
}
