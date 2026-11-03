/* boar_3: 8 functions, module ov073
 * mwccarm 1.2/base -O4,s
 * func_ov073_0227972c @ 0x0227972c, 0x118 bytes, Thumb
 * func_ov073_02279720 @ 0x02279720, 0xc bytes, Thumb
 * func_ov073_022796f0 @ 0x022796f0, 0x30 bytes, Thumb
 * func_ov073_022796c8 @ 0x022796c8, 0x28 bytes, Thumb
 * func_ov073_022796a8 @ 0x022796a8, 0x20 bytes, Thumb
 * func_ov073_022796a0 @ 0x022796a0, 0x8 bytes, Thumb
 * func_ov073_02279698 @ 0x02279698, 0x8 bytes, Thumb
 * func_ov073_0227964c @ 0x0227964c, 0x4c bytes, Thumb
 */

struct S_022796c8 {
    unsigned char pad_00[0x5c];
    unsigned int unk_5C;
    unsigned char pad_60[0x4];
    unsigned int unk_64;
};

typedef void *(*FuncType)(void *);

extern void *func_020edf70(int size);
extern void *func_0203f130(void *argument0);
extern void *func_0205467c(void *);
extern void func_0201b394(void *);
extern void *func_0201a430(void *);
extern int func_020169a8(void *);
extern int func_0201b324(void *);
extern void func_0201af14(void *);
extern void func_0201b370(void *);
extern void func_0201adec(void *);
extern void *func_0201a7ec(void *);
extern void func_0201a794(void *);
extern void *func_02032c64(void *);
extern void *func_02089c88(void *);
extern void *func_020f55cc(void *);
extern void func_02013c2c(void *);
extern void *func_02019eb0(void *);
extern void func_0201489c(void *);
extern void *func_02082f60(void *);
extern void *func_ov073_02278eb4(void *);
extern int data_020d8c64;
extern int data_020da088;
extern int data_ov073_02279b00;
extern int data_020c8120;
extern int func_0202edc8(char *);
extern void func_0201c280(char *, char *);
extern void func_ov073_02278d60(char *, char *);
extern int func_0202ec14(void *p);
extern int func_0208602c(void);
extern int func_020860b8(int a);
extern void func_02087864(int a, int b, int c);
extern int func_0202ec58(void *argument0);
extern void func_ov073_02279608(int a, int b);
extern int data_ov073_02279a4c;
extern int data_ov073_02279a1c;
extern unsigned char data_ov073_02279c1c[];
extern unsigned char data_ov073_02279c14[];

void *func_ov073_0227972c(void)
{
    void *p;

    p = func_020edf70(0x724);
    if (p != 0) {
        func_0203f130(p);
        *(void **) p = &data_020d8c64;
        *(unsigned short *) ((char *) p + 0xea) = 0xfff1;
        func_0205467c((char *) p + 0xec);
        func_0201b394((char *) p + 0x2a0);
        func_0201a430((char *) p + 0x2ac);
        func_020169a8((char *) p + 0x334);
        func_0201b324((char *) p + 0x350);
        func_0201af14((char *) p + 0x3a8);
        func_0201b370((char *) p + 0x3aa);
        func_0201adec((char *) p + 0x3b0);
        func_0201a7ec((char *) p + 0x418);
        func_0201a794((char *) p + 0x420);
        func_02032c64((char *) p + 0x49c);
        func_02089c88((char *) p + 0x4cc);
        func_020f55cc((char *) p + 0x514);
        func_02013c2c((char *) p + 0x558);
        func_02019eb0((char *) p + 0x564);
        func_0201489c((char *) p + 0x618);
        *(void **) p = &data_020da088;
        func_02082f60((char *) p + 0x640);
        *(void **) p = &data_ov073_02279b00;
        func_ov073_02278eb4((char *) p + 0x658);
    }
    return p;
}

int func_ov073_02279720(void)
{
    return data_020c8120;
}

int func_ov073_022796f0(char *x)
{
    if (func_0202edc8(x) == 0) {
        return 0;
    }
    func_0201c280(x, x + 0x658);
    func_ov073_02278d60(x + 0x658, x);
    return 1;
}

int func_ov073_022796c8(struct S_022796c8 *p)
{
    int v;

    v = func_0202ec14(p);
    if (v == 0) {
        return 0;
    }
    func_02087864(func_020860b8(func_0208602c()), p->unk_5C, p->unk_64);
    return 1;
}

int func_ov073_022796a8(int a)
{
    if (func_0202ec58((void *) a) == 0) {
        return 0;
    }
    func_ov073_02279608(a, 3);
    return 1;
}

int func_ov073_022796a0(void)
{
    return (int) &data_ov073_02279a4c;
}

int func_ov073_02279698(void)
{
    return (int) &data_ov073_02279a1c;
}

void *func_ov073_0227964c(void *self)
{
    char *s = (char *) self;
    unsigned int off;
    char *p;
    int adj;
    FuncType func;
    void *result = 0;

    off = (*(unsigned int *) (s + 0x654)) << 4;
    if (*(unsigned int *) (data_ov073_02279c1c + off) != 0) {
        p = (char *) data_ov073_02279c14 + off + 8;
        adj = *(int *) (p + 4);
        s += adj >> 1;
        if (adj & 1) {
            func = *(FuncType *) ((char *) (*(void **) s) + (unsigned int) *(unsigned int *) p);
        } else {
            func = *(FuncType *) p;
        }
        result = func((void *) s);
    }
    return result;
}
