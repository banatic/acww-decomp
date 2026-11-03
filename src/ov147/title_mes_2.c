/* title_mes_2: 5 functions, module ov147
 * mwccarm 1.2/base -O4,s
 * func_ov147_0229a6f0 @ 0x0229a6f0, 0xc bytes, Thumb
 * func_ov147_0229a6e4 @ 0x0229a6e4, 0xc bytes, Thumb
 * func_ov147_0229a6cc @ 0x0229a6cc, 0x18 bytes, Thumb
 * func_ov147_0229a6ac @ 0x0229a6ac, 0x20 bytes, Thumb
 * func_ov147_0229a6a8 @ 0x0229a6a8, 0x2 bytes, Thumb
 */

struct Struct_ov147_0229a6ac {
    int pad_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int pad_10;
    int pad_14;
    int unk_18;
};

extern int data_ov147_0229ac1c;
extern void func_020edb3c(void *p);
extern void func_ov147_0229a608(struct Struct_ov147_0229a6ac *p);
extern void func_ov147_0229a2f4(struct Struct_ov147_0229a6ac *p);

void func_ov147_0229a6f0(int **p)
{
    *p = &data_ov147_0229ac1c;
}

void func_ov147_0229a6e4(unsigned int *p)
{
    *p = (unsigned int) ((unsigned int *) &data_ov147_0229ac1c);
}

void *func_ov147_0229a6cc(void *self)
{
    *(void **) self = ((char *) &data_ov147_0229ac1c);
    func_020edb3c(self);
    return self;
}

void func_ov147_0229a6ac(struct Struct_ov147_0229a6ac *p)
{
    p->unk_04 = 0;
    p->unk_08 = 2;
    p->unk_18 = 0;
    p->unk_0C = 2;
    func_ov147_0229a608(p);
    func_ov147_0229a2f4(p);
}

void func_ov147_0229a6a8(void *receiver) {}
