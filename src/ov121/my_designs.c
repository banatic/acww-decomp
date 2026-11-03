/* my_designs: 5 functions, module ov121
 * mwccarm 1.2/base -O4,s
 * func_ov121_02299a5c @ 0x02299a5c, 0x12 bytes, Thumb
 * func_ov121_02299a4c @ 0x02299a4c, 0xe bytes, Thumb
 * func_ov121_02299a3c @ 0x02299a3c, 0xe bytes, Thumb
 * func_ov121_022999ec @ 0x022999ec, 0x50 bytes, Thumb
 * func_ov121_022999a0 @ 0x022999a0, 0x4c bytes, Thumb
 */

struct UnkStruct_02299a5c {
    char pad_00[0xa2];
    unsigned short flags;
};

struct UnkStruct_02299a3c {
    char pad_00[0xa2];
    unsigned short unk_A2;
};

extern char data_ov121_0229c3a8[];
extern void *func_ov002_02209ac8(void *);
extern void *func_ov002_0220ba0c(void *);
extern void *func_ov002_02209cb4(void *);
extern void *func_ov002_02207e28(void *);
extern void *func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);

int func_ov121_02299a5c(struct UnkStruct_02299a5c *self, int mask)
{
    if (self->flags & mask) {
        return 1;
    }
    return 0;
}

void func_ov121_02299a4c(unsigned short *param0, unsigned short param1)
{
    unsigned short *ptr = (unsigned short *) ((char *) param0 + 0xa2);
    *ptr = (unsigned short) (*ptr | param1);
}

void func_ov121_02299a3c(struct UnkStruct_02299a3c *p, unsigned short mask)
{
    p->unk_A2 &= ~mask;
}

void *func_ov121_022999ec(void *self)
{
    *(void **) self = data_ov121_0229c3a8;
    func_ov002_02209ac8((char *) self + 0x528);
    func_ov002_0220ba0c((char *) self + 0x40c);
    func_ov002_02209cb4((char *) self + 0x3a8);
    func_ov002_02207e28((char *) self + 0x2d8);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}

void *func_ov121_022999a0(void *self)
{
    *(void **) self = ((char *) data_ov121_0229c3a8);
    func_ov002_02209ac8((char *) self + 0x528);
    func_ov002_0220ba0c((char *) self + 0x40c);
    func_ov002_02209cb4((char *) self + 0x3a8);
    func_ov002_02207e28((char *) self + 0x2d8);
    func_ov002_0220826c(self);
    return self;
}
