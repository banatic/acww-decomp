/* building_lights: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b34e0 @ 0x020b34e0, 0x22 bytes, Thumb
 * func_020b3438 @ 0x020b3438, 0xa8 bytes, Thumb
 * func_020b3428 @ 0x020b3428, 0x10 bytes, Thumb
 * func_020b3408 @ 0x020b3408, 0x20 bytes, Thumb
 * func_020b33e0 @ 0x020b33e0, 0x28 bytes, Thumb
 * func_020b33b8 @ 0x020b33b8, 0x28 bytes, Thumb
 * func_020b3380 @ 0x020b3380, 0x38 bytes, Thumb
 * func_020b3340 @ 0x020b3340, 0x40 bytes, Thumb
 * func_020b3328 @ 0x020b3328, 0x18 bytes, Thumb
 * func_020b3310 @ 0x020b3310, 0x18 bytes, Thumb
 */

struct _S {
    unsigned char pad_00[0x18];
    unsigned char count;
};

typedef struct {
    char data[0x40];
} UnkStruct_020b33b8;

extern int func_020b365c(int a, int b, int c);
extern void NNSi_G3dModifyMatFlag(struct _S *a, int b, int c);
extern void NNS_G3dMdlSetMdlEmi(struct _S *a, int b, int c);
extern int data_027e0148;
extern int func_02064328(void *p1, void *p2, int p3);
extern unsigned char data_020e50f4[];
extern unsigned char data_021f4b58[];
extern void func_020b3740(void *);
extern void func_020b3650(void *);
extern void *func_020b356c(void *);
extern void func_020b35e0(void *);
extern void func_020b35d8(void *);
extern void *func_020b3550(void *);
extern void func_020b364c(void *);
extern void func_020b373c(void *);
extern void func_020b3720(void *param1, void *param2);
extern void func_020b3634(void *param1, void *param2);
extern void func_020b3504(void *param1, void *param2);
extern void func_020b35c0(void *param1, void *param2);
extern void func_020b36c8(void *);
extern int func_020b3658(void *);
extern void func_020b3598(void *, void *, int);
extern void func_020b35e8(void *, void *, int);
extern int func_020b3670(int a, int b, int c, int d, int e);

int func_020b3428(void);

int func_020b34e0(signed char *base, int value)
{
    signed char *p = base + 4;
    while (p < base + 7) {
        if (*p == value) {
            return 1;
        }
        p++;
    }
    return 0;
}

void func_020b3438(void *arg0, struct _S *arg1, int arg2)
{
    int i;
    int v6;
    int v7;
    int v8;
    int v9;
    int v10;
    int value;

    if (arg2 != 0) {
        v6 = (NNSi_G3dModifyMatFlag(arg1, 1, 0x400), func_020b3428());

        v7 = func_020b365c(arg2, ((v6 >> 10) & 0x1f) << 12, 0x1f000);
        v8 = func_020b365c(arg2, (v6 & 0x1f) << 12, 0x1f000);
        v9 = func_020b365c(arg2, ((v6 >> 5) & 0x1f) << 12, 0x1f000);

        v10 = ((v7 >> 12) << 10) | ((v8 >> 12) | ((v9 >> 12) << 5));
        v7 = (unsigned short) v10;

        for (i = 0; i < arg1->count; i++) {
            if (func_020b34e0((signed char *) arg0, i) != 0) {
                value = v7;
            } else {
                value = v6;
            }
            NNS_G3dMdlSetMdlEmi(arg1, i, value);
        }
    } else {
        NNSi_G3dModifyMatFlag(arg1, 0, 0x400);
    }
}

int func_020b3428(void)
{
    return (int) ((unsigned int) (((int) ((unsigned int) (*(int *) ((char *) ((int) &data_027e0148) + (24))) >> 16) << 16)) >>
                  16);
}

void *func_020b3408(int unused, int param)
{
    func_02064328((void *) data_021f4b58, (void *) data_020e50f4, param);
    return (void *) data_021f4b58;
}

void *func_020b33e0(void *base)
{
    func_020b3740(base);
    func_020b3650((char *) base + 0x14);
    func_020b356c((char *) base + 0x18);
    func_020b35e0((char *) base + 0x34);
    return base;
}

UnkStruct_020b33b8 *func_020b33b8(UnkStruct_020b33b8 *self)
{
    func_020b35d8(&self->data[0x34]);
    func_020b3550(&self->data[0x18]);
    func_020b364c(&self->data[0x14]);
    func_020b373c(self);
    return self;
}

void func_020b3380(void *param1, void *param2, void *param3)
{
    void *r5 = param1;
    void *r4 = param2;
    void *r1 = param3;

    func_020b3720(r5, r1);

    if (r4 != 0) {
        func_020b3634((char *) r5 + 0x14, r4);
        func_020b3504((char *) r5 + 0x18, r4);
        func_020b35c0((char *) r5 + 0x34, r4);
    }
}

void func_020b3340(void *p1, void *p2)
{
    char *base;
    int r6;

    base = (char *) p1;
    func_020b36c8(p1);
    r6 = func_020b3658(p1);
    if (p2 != 0) {
        func_020b3438(base + 0x18, (struct _S *) p2, r6);
        func_020b3598(base + 0x34, p2, r6);
        base += 0x14;
        func_020b35e8(base, p2, r6);
    }
}

void func_020b3328(int a, int b, int c, int d)
{
    func_020b3670(a, b, c, d, 0x800);
}

int func_020b3310(int *argument0)
{
    int result;
    if (func_020b3658((void *) ((int *) argument0)) != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
