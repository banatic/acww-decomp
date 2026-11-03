/* birthday_screen: 8 functions, module ov137
 * mwccarm 1.2/base -O4,s
 * func_ov137_0229c650 @ 0x0229c650, 0x18 bytes, Thumb
 * func_ov137_0229c628 @ 0x0229c628, 0x28 bytes, Thumb
 * func_ov137_0229c58c @ 0x0229c58c, 0x9c bytes, Thumb
 * func_ov137_0229c574 @ 0x0229c574, 0x18 bytes, Thumb
 * func_ov137_0229c564 @ 0x0229c564, 0x10 bytes, Thumb
 * func_ov137_0229c554 @ 0x0229c554, 0x10 bytes, Thumb
 * func_ov137_0229c518 @ 0x0229c518, 0x3c bytes, Thumb
 * func_ov137_0229c4e0 @ 0x0229c4e0, 0x38 bytes, Thumb
 */

struct func_ov137_0229c58c_s {
    unsigned char pad_00[0x2b77];
    unsigned char byte;
};

extern void func_ov002_0220a1dc(void *p);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern void func_ov002_0220a164(void *p);
extern unsigned char data_ov137_0229d35c[];
extern unsigned char data_ov137_0229d358[];
extern unsigned char data_ov137_0229d364[];
extern unsigned char data_ov137_0229d360[];
extern int func_ov002_022088ac(int);
extern int func_ov002_0220889c(int);
extern int func_ov002_022088cc(int);
extern int func_ov002_022088bc(int);
extern char data_ov137_0229d440;
extern char *func_ov134_0229beb0(void *);
extern void *func_ov002_0220afdc(void *);
extern void *func_ov002_02209cb4(void *);
extern void *func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);

void func_ov137_0229c650(void *self)
{
    func_ov002_0220a1dc((char *) self + 0x94);
    func_ov002_02208098(self, 9);
}

void func_ov137_0229c628(void *self)
{
    func_ov002_0220a164((unsigned char *) self + 0x94);
    *((unsigned char *) self + 0x2b76) = *((unsigned char *) self + 0x8d);
    func_ov002_02208098(self, 10);
}

int func_ov137_0229c58c(struct func_ov137_0229c58c_s *self, int param)
{
    unsigned char old;

    old = self->byte;
    if (func_ov002_022088ac(param)) {
        self->byte = data_ov137_0229d35c[self->byte];
    } else if (func_ov002_0220889c(param)) {
        self->byte = data_ov137_0229d358[self->byte];
    }
    if (old != self->byte) {
        return 1;
    }
    if (func_ov002_022088cc(param)) {
        self->byte = data_ov137_0229d364[self->byte];
    } else if (func_ov002_022088bc(param)) {
        self->byte = data_ov137_0229d360[self->byte];
    }
    if (old != self->byte) {
        return 1;
    }
    return 0;
}

int func_ov137_0229c574(unsigned short *p, unsigned short mask)
{
    if ((p[0x15ba] & mask) != 0) {
        return 1;
    }
    return 0;
}

void func_ov137_0229c564(unsigned short *p, unsigned short v)
{
    p = (unsigned short *) ((char *) p + 0x2b74);
    *p = (unsigned short) (*p | v);
}

void func_ov137_0229c554(unsigned short *base, unsigned short mask)
{
    base = (unsigned short *) ((char *) base + 0x2b74);
    *base &= ~mask;
}

void *func_ov137_0229c518(void *self)
{
    *(void **) self = &data_ov137_0229d440;
    func_ov134_0229beb0((char *) self + 0x2c4);
    func_ov002_0220afdc((char *) self + 0xf8);
    func_ov002_02209cb4((char *) self + 0x94);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}

void *func_ov137_0229c4e0(void *self)
{
    *(void **) self = &data_ov137_0229d440;
    func_ov134_0229beb0((char *) self + 0x2c4);
    func_ov002_0220afdc((char *) self + 0xf8);
    func_ov002_02209cb4((char *) self + 0x94);
    func_ov002_0220826c(self);
    return self;
}
