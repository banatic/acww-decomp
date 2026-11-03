/* date_screen: 8 functions, module ov138
 * mwccarm 1.2/base -O4,s
 * func_ov138_0229c654 @ 0x0229c654, 0x18 bytes, Thumb
 * func_ov138_0229c630 @ 0x0229c630, 0x24 bytes, Thumb
 * func_ov138_0229c588 @ 0x0229c588, 0xa8 bytes, Thumb
 * func_ov138_0229c574 @ 0x0229c574, 0x12 bytes, Thumb
 * func_ov138_0229c564 @ 0x0229c564, 0xe bytes, Thumb
 * func_ov138_0229c554 @ 0x0229c554, 0xe bytes, Thumb
 * func_ov138_0229c518 @ 0x0229c518, 0x3c bytes, Thumb
 * func_ov138_0229c4e0 @ 0x0229c4e0, 0x38 bytes, Thumb
 */

struct UnkStruct_0229c574 {
    unsigned char pad_00[0x92];
    unsigned short unk_92;
};

struct UnkStruct_0229c554 {
    char pad_00[0x92];
    unsigned short unk_92;
};

struct UnkStruct_0229c4e0 {
    void *unk_00;
};

extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_0220a164(void *);
extern int func_ov002_022088ac(int);
extern int func_ov002_0220889c(int);
extern int func_ov002_022088cc(int);
extern int func_ov002_022088bc(int);
extern const unsigned char data_ov138_0229d3e4[];
extern const unsigned char data_ov138_0229d3ec[];
extern const unsigned char data_ov138_0229d3fc[];
extern const unsigned char data_ov138_0229d3f4[];
extern char *func_ov134_0229beb0(void *p);
extern void *func_ov002_0220afdc(void *p);
extern void *func_ov002_02209cb4(void *p);
extern void *func_ov002_0220826c(void *p);
extern void func_ov002_02207f6c(void *p);
extern char data_ov138_0229d4e0[];

void func_ov138_0229c654(void *self)
{
    func_ov002_0220a1dc((char *) self + 0x98);
    func_ov002_02208098((void *) (self), 9);
}

void func_ov138_0229c630(void *self)
{
    unsigned char b;
    void *p;

    p = (char *) self + 0x98;
    func_ov002_0220a164(p);

    b = *(unsigned char *) ((char *) self + 0x8d);
    *(unsigned char *) ((char *) self + 0x94) = b;

    func_ov002_02208098((void *) (self), 0xa);
}

int func_ov138_0229c588(void *obj, int mode)
{
    unsigned char orig;
    unsigned char *p;

    orig = ((unsigned char *) obj)[0x95];
    if (func_ov002_022088ac(mode)) {
        ((unsigned char *) obj)[0x95] = data_ov138_0229d3e4[((unsigned char *) obj)[0x95]];
    } else if (func_ov002_0220889c(mode)) {
        ((unsigned char *) obj)[0x95] = data_ov138_0229d3ec[((unsigned char *) obj)[0x95]];
    }
    if (orig != ((unsigned char *) obj)[0x95]) {
        return 1;
    }
    if (func_ov002_022088cc(mode)) {
        ((unsigned char *) obj)[0x95] = data_ov138_0229d3fc[((unsigned char *) obj)[0x95]];
    } else if (func_ov002_022088bc(mode)) {
        ((unsigned char *) obj)[0x95] = data_ov138_0229d3f4[((unsigned char *) obj)[0x95]];
    }
    p = ((unsigned char *) obj) + 0x95;
    if (orig == *p) {
        return 0;
    } else {
        return 1;
    }
}

int func_ov138_0229c574(struct UnkStruct_0229c574 *p, unsigned short mask)
{
    if ((p->unk_92 & mask) != 0) {
        return 1;
    }
    return 0;
}

void func_ov138_0229c564(unsigned short *p, unsigned short v)
{
    p[0x49] |= v;
}

void func_ov138_0229c554(struct UnkStruct_0229c554 *self, unsigned short mask)
{
    unsigned short temp = self->unk_92;
    self->unk_92 = temp & ~mask;
}

void *func_ov138_0229c518(void *p)
{
    char *self = (char *) p;
    *(unsigned int *) self = (unsigned int) ((char *) data_ov138_0229d4e0);
    func_ov134_0229beb0(self + 0x2c8);
    func_ov002_0220afdc(self + 0xfc);
    func_ov002_02209cb4(self + 0x98);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}

void *func_ov138_0229c4e0(struct UnkStruct_0229c4e0 *obj)
{
    obj->unk_00 = &data_ov138_0229d4e0;
    func_ov134_0229beb0((char *) obj + 0x2c8);
    func_ov002_0220afdc((char *) obj + 0xfc);
    func_ov002_02209cb4((char *) obj + 0x98);
    func_ov002_0220826c(obj);
    return obj;
}
