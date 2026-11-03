/* carried_letters_4: 5 functions, module ov103
 * mwccarm 1.2/base -O4,s
 * func_ov103_0229ca48 @ 0x0229ca48, 0x54 bytes, Thumb
 * func_ov103_0229ca00 @ 0x0229ca00, 0x48 bytes, Thumb
 * func_ov103_0229c9c8 @ 0x0229c9c8, 0x38 bytes, Thumb
 * func_ov103_0229c994 @ 0x0229c994, 0x34 bytes, Thumb
 * func_ov103_0229c964 @ 0x0229c964, 0x30 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x218c];
    void *obj_218c;
    unsigned char pad_2190[0xC12];
    unsigned char unk_2DA2;
    unsigned char pad_2DA3;
    unsigned char unk_2DA4;
} UnkStruct_0229ca48;

struct UnkStruct_0229c9c8 {
    char pad_00[0x2b90];
    unsigned int src1;
    unsigned int src2;
    unsigned int dst1;
    unsigned int dst2;
};

struct struct_ov103_0229c994 {
    char pad_00[0x2274];
    char unk_2274;
    char pad_2275[0x923];
    int unk_2B98;
    int unk_2B9C;
};

struct UnkStruct_0229c964 {
    char pad_00[0x225c];
    char sub;
    char pad_225D[0x93b];
    int unk_2B98;
    int unk_2B9C;
};

extern int func_ov103_0229cdfc(const UnkStruct_0229ca48 *, unsigned char);
extern int func_ov103_0229cc08(const UnkStruct_0229ca48 *, unsigned char);
extern void func_ov002_02207cf0(void *);
extern void func_ov002_02207cf8(void *);
extern int func_ov103_0229c2f4(void *obj, int arg);
extern void func_ov094_0229b5e8(void *arg0, int arg1, int arg2, void *arg3);
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov002_02209f3c(void *ptr);
extern int func_ov002_02209f14(void *ptr);
extern int func_ov002_02209d84(void *p);
extern int func_ov002_02209d7c(void *p);

void func_ov103_0229ca48(UnkStruct_0229ca48 *p)
{
    if (func_ov103_0229cdfc(p, p->unk_2DA4) != 0) {
        if (func_ov103_0229cc08(p, p->unk_2DA4) != 0) {
            func_ov002_02207cf0(&p->obj_218c);
            return;
        } else {
            p->unk_2DA2 = p->unk_2DA4;
            func_ov002_02207cf8(&p->obj_218c);
            return;
        }
    } else {
        func_ov002_02207cf0(&p->obj_218c);
        return;
    }
}

void func_ov103_0229ca00(void *obj)
{
    unsigned char b;

    if (func_ov103_0229c2f4(obj, 0x40)) {
        return;
    }

    b = ((unsigned char *) obj)[0x2da0];
    if (b != 0 && b == 1) {
        func_ov094_0229b5e8((char *) obj + 0xb2c, *(int *) ((char *) obj + 0x2b98), *(int *) ((char *) obj + 0x2b9c),
                            (char *) obj + 0x2ba0);
    }
}

void func_ov103_0229c9c8(struct UnkStruct_0229c9c8 *p)
{
    p->dst1 = p->src1 + data_021f6c58;
    p->dst2 = p->src2 + data_021f6c54;
}

void func_ov103_0229c994(struct struct_ov103_0229c994 *self)
{
    self->unk_2B98 = func_ov002_02209f3c(&self->unk_2274) - 2;
    self->unk_2B9C = func_ov002_02209f14(&self->unk_2274) - 4;
}

void func_ov103_0229c964(struct UnkStruct_0229c964 *self)
{
    self->unk_2B98 = func_ov002_02209d84(&self->sub);
    self->unk_2B9C = func_ov002_02209d7c(&self->sub);
}
