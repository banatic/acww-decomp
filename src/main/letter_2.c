/* letter_2: 12 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02066830 @ 0x02066830, 0x1c bytes, Thumb
 * func_02066788 @ 0x02066788, 0xa6 bytes, Thumb
 * func_0206671c @ 0x0206671c, 0x6c bytes, Thumb
 * func_02066708 @ 0x02066708, 0x12 bytes, Thumb
 * func_020666f8 @ 0x020666f8, 0xe bytes, Thumb
 * func_020666e4 @ 0x020666e4, 0x14 bytes, Thumb
 * func_020666d0 @ 0x020666d0, 0x14 bytes, Thumb
 * func_020666bc @ 0x020666bc, 0x14 bytes, Thumb
 * func_020666b4 @ 0x020666b4, 0x6 bytes, Thumb
 * func_020666b0 @ 0x020666b0, 0x4 bytes, Thumb
 * func_020666a0 @ 0x020666a0, 0xe bytes, Thumb
 * func_02066694 @ 0x02066694, 0xc bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x10];
    unsigned char data[6];
    unsigned char pad_16[0x8];
    unsigned char type;
} UnkStruct_02066788;

struct Param {
    unsigned char pad_00[0x1e];
    unsigned char mode;
};

struct _Info {
    unsigned char data[0x1e];
    unsigned char type;
};

struct UnkStruct_020666f8 {
    unsigned char pad_00[0x1E];
    unsigned char flag;
};

typedef struct {
    unsigned char pad_00[30];
    unsigned char unk_1E;
} UnkStruct_020666b4;

struct UnkStruct_020666a0 {
    char pad_00[0x1E];
    unsigned char unk_1E;
};

extern void MI_CpuCopy8(int, int, int);
extern void *func_02094fd4(void *);
extern void *func_02094f7c(void *);
extern int func_02003780(void *);
extern void *func_02070c08(void *);
extern void func_02051c08(void *, void *, int);
extern void func_020037ac(void *, void *);
extern int func_02003618(void *, void *);
extern int func_020a87e0(void *, void *);
extern void func_02094f34(void *, void *, int);
extern int func_0207094c(void *, int);
extern void func_020708b4(void *, void *);
extern int **func_02070be8(void *);
extern int func_02003750(void *);
extern void *func_02094f64(void *);
extern void *func_02094fbc(void *);
extern void *func_0209529c(void *);
extern void func_02095208(void *, void *);
extern void *func_02095074(void *, void *);
extern int func_0209526c(void *);
extern void func_02003790(void *param1, void *param2);
extern void func_020951dc(void *a, void *b);
extern void data_020de760(void);

int func_02066830(int a, int b)
{
    MI_CpuCopy8(b, a, 0x100);
    return a;
}

void *func_02066788(UnkStruct_02066788 *s, void *arg1)
{
    unsigned char obj0[0x20];
    unsigned char obj1[0x1c];
    unsigned char obj2[0x10];
    unsigned char obj3[0x70];

    func_02094fd4(obj0);
    func_02094f7c(obj1);
    func_02003780(obj2);
    func_02070c08(obj3);

    switch (s->type) {
        case 1:
        case 2:
            func_02051c08(s->data, arg1, 6);
            break;
        case 3:
            func_020037ac(obj2, s);
            func_02003618(obj2, obj0);
            func_020a87e0(obj1, obj0);
            func_02094f34(obj1, arg1, 6);
            break;
        case 7:
            func_0207094c(obj3, 0x43);
            func_020708b4(obj3, arg1);
            break;
        default:
            break;
    }

    func_02070be8(obj3);
    func_02003750(obj2);
    func_02094f64(obj1);
    return func_02094fbc(obj0);
}

int func_0206671c(struct Param *p, void *q)
{
    unsigned char obj0[16];
    unsigned char obj1[36];

    func_02003780(&obj0);
    func_0209529c(&obj1);

    switch (p->mode) {
        case 1:
        case 2:
        case 6:
            func_02095208(&obj1, p);
            func_02095074(&obj1, q);
            break;
        case 3:
        case 5:
            func_020037ac(&obj0, p);
            func_02003618(&obj0, q);
            break;
    }

    func_0209526c(&obj1);
    return func_02003750(&obj0);
}

void *func_02066708(struct _Info *obj)
{
    if (obj->type == 1 || obj->type == 2 || obj->type == 6) {
        return obj;
    } else {
        return 0;
    }
}

void *func_020666f8(struct UnkStruct_020666f8 *arg0)
{
    if (arg0->flag == 3 || arg0->flag == 5) {
        return arg0;
    } else {
        return 0;
    }
}

void func_020666e4(void *param1, void *param2)
{
    unsigned char *ptr = (unsigned char *) param1;
    ptr[0x1e] = 3;
    func_02003790(param2, param1);
}

void func_020666d0(void *arg0, void *arg1)
{
    unsigned char *p = (unsigned char *) arg0;
    p[0x1e] = 2;
    func_020951dc(arg1, arg0);
}

void func_020666bc(void *a, void *b)
{
    unsigned char *p = (unsigned char *) a;
    p[0x1e] = 1;
    func_020951dc(b, a);
}

void func_020666b4(UnkStruct_020666b4 *p)
{
    p->unk_1E = 7;
}

void func_020666b0(unsigned char *p0, int p1)
{
    p0[30] = p1;
}

int func_020666a0(struct UnkStruct_020666a0 *s, int value)
{
    if (s->unk_1E == value) {
        return 1;
    } else {
        return 0;
    }
}

void func_02066694(int *r0)
{
    *r0 = (int) data_020de760;
}
