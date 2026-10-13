/* func_ov105_0229cdf0 @ 0x0229cdf0, 0x64 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov105_0229c340(void *self, unsigned int);
extern int func_ov002_02208ae4(void *p);
extern int func_ov002_02208ad8(void *p, unsigned char);
extern void func_ov002_0220a0b4(void *p, int, int);
extern void func_ov002_0220a374(void *p, int);

typedef struct {
    unsigned char pad_00[0x2bf];
    unsigned char unk_2BF;
    unsigned char pad_2C0[0x21e4];
    unsigned char sub2[1];
    unsigned char pad_24A5[0x63];
    unsigned char sub1[1];
} UnkStruct_0229cdf0;

void func_ov105_0229cdf0(UnkStruct_0229cdf0 *self)
{
    int r4;
    int r2;

    if (func_ov105_0229c340(self, 0x800)) {
        self->unk_2BF = 1;
    } else {
        self->unk_2BF = 0;
    }
    r4 = func_ov002_02208ae4(&self->sub1);
    r2 = func_ov002_02208ad8(&self->sub1, self->unk_2BF);
    func_ov002_0220a0b4(&self->sub2, r4, r2);
    func_ov002_0220a374(&self->sub2, 7);
}
