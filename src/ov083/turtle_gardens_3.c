/* turtle_gardens_3: 5 functions, module ov083
 * mwccarm 1.2/base -O4,s
 * func_ov083_02278fe8 @ 0x02278fe8, 0x118 bytes, Thumb
 * func_ov083_02278fb8 @ 0x02278fb8, 0x30 bytes, Thumb
 * func_ov083_02278f38 @ 0x02278f38, 0x80 bytes, Thumb
 * func_ov083_02278f30 @ 0x02278f30, 0x8 bytes, Thumb
 * func_ov083_02278f28 @ 0x02278f28, 0x8 bytes, Thumb
 */

typedef struct {
    char pad_00[0x65c];
    void *unk_65C;
} UnkStruct_02278fb8;

extern void *func_020edf70(int size);
extern void *func_0203f130(void *p);
extern void *func_0205467c(void *p);
extern void func_0201b394(void *p);
extern void *func_0201a430(void *p);
extern int func_020169a8(void *p);
extern int func_0201b324(void *p);
extern void func_0201af14(void *p);
extern void func_0201b370(void *p);
extern void func_0201adec(void *p);
extern void *func_0201a7ec(void *p);
extern void func_0201a794(void *p);
extern void *func_02032c64(void *p);
extern void *func_02089c88(void *p);
extern void *func_020f55cc(void *p);
extern void func_02013c2c(void *p);
extern void *func_02019eb0(void *p);
extern void func_0201489c(void *p);
extern void *func_02082f60(void *p);
extern void *func_ov083_02278d7c(void *p);
extern char data_020d8c64[];
extern char data_020da088[];
extern char data_ov083_0227928c[];
extern int func_0202edc8(UnkStruct_02278fb8 *p);
extern void func_0201c280(UnkStruct_02278fb8 *p, void *q);
extern void func_ov083_02278d20(void *q, UnkStruct_02278fb8 *p);
extern int func_0202ec58(void *);
extern void func_ov083_02278e98(void *, int);
extern void func_02016764(void *, void *, int, int, int, int, int, int);
extern void func_02054188(void *, int, int);
extern int func_0203fdc4(int);
extern void func_020865d8(int, int);
extern unsigned char data_021f3aa4[];
extern int data_ov083_022791d8;
extern int data_ov083_022791a8;

void *func_ov083_02278fe8(void)
{
    unsigned char *p;

    p = func_020edf70(0x71c);
    if (p != 0) {
        func_0203f130(p);

        *(void **) p = data_020d8c64;
        *(unsigned short *) (p + 0xea) = 0xfff1;
        func_0205467c(p + 0xec);
        func_0201b394(p + 0x2a0);
        func_0201a430(p + 0x2ac);
        func_020169a8(p + 0x334);
        func_0201b324(p + 0x350);
        func_0201af14(p + 0x3a8);
        func_0201b370(p + 0x3aa);
        func_0201adec(p + 0x3b0);
        func_0201a7ec(p + 0x418);
        func_0201a794(p + 0x420);
        func_02032c64(p + 0x49c);
        func_02089c88(p + 0x4cc);
        func_020f55cc(p + 0x514);
        func_02013c2c(p + 0x558);
        func_02019eb0(p + 0x564);
        func_0201489c(p + 0x618);
        *(void **) p = data_020da088;
        func_02082f60(p + 0x640);
        *(void **) p = data_ov083_0227928c;
        func_ov083_02278d7c(p + 0x65c);
    }
    return p;
}

int func_ov083_02278fb8(UnkStruct_02278fb8 *p)
{
    if (func_0202edc8(p) == 0) {
        return 0;
    }
    func_0201c280(p, &p->unk_65C);
    func_ov083_02278d20(&p->unk_65C, p);
    return 1;
}

int func_ov083_02278f38(void *p)
{
    if (func_0202ec58(p) == 0) {
        return 0;
    }
    func_ov083_02278e98(p, 0);
    func_02016764((char *) p + 0x334, p, 0x140, 0, 0, 0x1000, 0, 1);
    func_02054188((char *) p + 0xec, 0xc, 0xe);
    *(unsigned int *) ((char *) p + 0x4e8) |= 2;
    *((unsigned char *) p + 0x718) = (unsigned char) func_0203fdc4(0xe);
    func_020865d8((unsigned int) data_021f3aa4, 0);
    return 1;
}

int func_ov083_02278f30(void)
{
    return (int) &data_ov083_022791d8;
}

int func_ov083_02278f28(void)
{
    return (int) &data_ov083_022791a8;
}
