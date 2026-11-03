/* star_designer: 5 functions, module ov129
 * mwccarm 1.2/base -O4,s
 * func_ov129_0229b7ec @ 0x0229b7ec, 0x12 bytes, Thumb
 * func_ov129_0229b7dc @ 0x0229b7dc, 0xe bytes, Thumb
 * func_ov129_0229b7cc @ 0x0229b7cc, 0xe bytes, Thumb
 * func_ov129_0229b774 @ 0x0229b774, 0x58 bytes, Thumb
 * func_ov129_0229b720 @ 0x0229b720, 0x54 bytes, Thumb
 */

struct UnkStruct_0229b7ec {
    unsigned char pad_00[0xA4];
    unsigned short unk_A4;
};

typedef struct {
    char pad_00[0xa4];
    unsigned short unk_A4;
} UnkStruct_0229b7dc;

struct UnkStruct_0229b7cc {
    char pad_00[0xA4];
    unsigned short unk_A4;
};

typedef struct {
    void *unk_00;
} UnkStruct_0229b720;

extern unsigned char data_ov129_0229dc38;
extern void func_ov127_0229a0e8(void *);
extern void func_020b18a8(void *);
extern void *func_ov002_02209cb4(void *);
extern void *func_ov002_0220afdc(void *);
extern void *func_ov002_0220ba0c(void *);
extern void *func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);

int func_ov129_0229b7ec(struct UnkStruct_0229b7ec *p, unsigned short mask)
{
    unsigned int combined = p->unk_A4 & mask;
    if (combined != 0) {
        return 1;
    }
    return 0;
}

void func_ov129_0229b7dc(UnkStruct_0229b7dc *p, unsigned short v)
{
    unsigned short tmp = p->unk_A4;
    tmp |= v;
    p->unk_A4 = tmp;
}

void func_ov129_0229b7cc(struct UnkStruct_0229b7cc *p, unsigned short mask)
{
    p->unk_A4 = p->unk_A4 & ~mask;
}

void *func_ov129_0229b774(void *p)
{
    *(void **) p = (void *) &data_ov129_0229dc38;
    func_ov127_0229a0e8((char *) p + 0x734);
    func_020b18a8((char *) p + 0x404);
    func_ov002_02209cb4((char *) p + 0x3a0);
    func_ov002_0220afdc((char *) p + 0x1d4);
    func_ov002_0220ba0c((char *) p + 0xb8);
    func_ov002_0220826c(p);
    func_ov002_02207f6c(p);
    return p;
}

UnkStruct_0229b720 *func_ov129_0229b720(UnkStruct_0229b720 *self)
{
    self->unk_00 = ((char *) &data_ov129_0229dc38);
    func_ov127_0229a0e8((char *) self + 0x734);
    func_020b18a8((char *) self + 0x404);
    func_ov002_02209cb4((char *) self + 0x3a0);
    func_ov002_0220afdc((char *) self + 0x1d4);
    func_ov002_0220ba0c((char *) self + 0xb8);
    func_ov002_0220826c(self);
    return self;
}
