/* star_view: 5 functions, module ov128
 * mwccarm 1.2/base -O4,s
 * func_ov128_0229b7ec @ 0x0229b7ec, 0x18 bytes, Thumb
 * func_ov128_0229b7dc @ 0x0229b7dc, 0x10 bytes, Thumb
 * func_ov128_0229b7cc @ 0x0229b7cc, 0x10 bytes, Thumb
 * func_ov128_0229b774 @ 0x0229b774, 0x58 bytes, Thumb
 * func_ov128_0229b720 @ 0x0229b720, 0x54 bytes, Thumb
 */

typedef struct UnkWork {
    void *unk_00;
} UnkWork;

extern char data_ov128_0229cbc0;
extern int **func_02070be8(void *);
extern void func_ov127_0229a0e8(void *);
extern void func_020b18a8(void *);
extern void *func_ov002_02209cb4(void *);
extern void *func_ov002_0220b3a4(void *);
extern void *func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);

int func_ov128_0229b7ec(unsigned char *base, unsigned short mask)
{
    unsigned short v = *(unsigned short *) (base + 0x2d68);
    v &= mask;
    if (v == 0) {
        return 0;
    } else {
        return 1;
    }
}

void func_ov128_0229b7dc(unsigned short *base, unsigned short value)
{
    base[0x16b4] |= value;
}

void func_ov128_0229b7cc(char *base, unsigned short mask)
{
    *(unsigned short *) (base + 0x2d68) &= ~mask;
}

UnkWork *func_ov128_0229b774(UnkWork *self)
{
    self->unk_00 = &data_ov128_0229cbc0;
    func_02070be8((char *) self + 0x2cdc);
    func_ov127_0229a0e8((char *) self + 0x4a4);
    func_020b18a8((char *) self + 0x174);
    func_ov002_02209cb4((char *) self + 0x110);
    func_ov002_0220b3a4((char *) self + 0x94);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}

void *func_ov128_0229b720(void *self)
{
    char *p = (char *) self;
    *(unsigned int *) p = (unsigned int) ((int *) &data_ov128_0229cbc0);
    func_02070be8(p + 0x2cdc);
    func_ov127_0229a0e8(p + 0x4a4);
    func_020b18a8(p + 0x174);
    func_ov002_02209cb4(p + 0x110);
    func_ov002_0220b3a4(p + 0x94);
    func_ov002_0220826c(p);
    return self;
}
