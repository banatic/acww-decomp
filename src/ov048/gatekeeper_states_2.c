/* gatekeeper_states_2: 7 functions, module ov048
 * mwccarm 1.2/base -O4,s
 * func_ov048_022629e4 @ 0x022629e4, 0x4 bytes, Thumb
 * func_ov048_02262958 @ 0x02262958, 0x8c bytes, Thumb
 * func_ov048_02262954 @ 0x02262954, 0x4 bytes, Thumb
 * func_ov048_022628b8 @ 0x022628b8, 0x9c bytes, Thumb
 * func_ov048_022628b4 @ 0x022628b4, 0x4 bytes, Thumb
 * func_ov048_02262880 @ 0x02262880, 0x32 bytes, Thumb
 * func_ov048_0226287c @ 0x0226287c, 0x4 bytes, Thumb
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_02262958;

typedef struct {
    char pad_00[0x5c];
    UnkStruct_02262958 sub;
    char pad_68[0x26];
    short sfield;
} PStruct;

typedef struct {
    char pad_00[4];
    int unk_04;
} EarlyStruct;

struct UnkStruct_022628b8_3;

struct UnkStruct_022628b8_2 {
    int pad_00;
    int type;
};

struct UnkStruct_022628b8 {
    char pad_00[0x5c];
    int vec[3];
    char pad_68[0x8e - 0x68];
    short s;
};

struct UnkStruct_022628b8_3 {
    char pad_00[0x8e];
    short s;
};

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_02262880;

extern void *func_020682e0(int);
extern int func_0208602c(void);
extern int func_020860cc(int);
extern void *func_020961a8(int);
extern void func_0204f818(int *, int *, int *);
extern void func_02087e88(int, int);
extern void func_02087e80(int, int);
extern void func_0203acd8(void);
extern void func_020a18f4(void);
extern int func_020b5e10(void);
extern int func_020b63f4(int, int, int *, unsigned int, int, int, int);
extern void func_ov048_022635f4(void *, int);
extern int func_020b5f84(int, int, int *, int, int, int, int);
extern void func_020a18d0(void);
extern int func_020b6434(int, int, int, int);
extern void func_020a193c(void);

int func_ov048_022629e4(void)
{
    return 1;
}

int func_ov048_02262958(void *obj)
{
    int a, b;
    int r4;
    int r6;
    int sub[3];
    PStruct *p;
    EarlyStruct *e;
    UnkStruct_02262958 *sp;

    e = func_020682e0(0);
    if (e->unk_04 == 5) {
        r6 = func_020860cc((int) func_0208602c());
        p = func_020961a8(4);
        sp = &p->sub;
        sub[0] = p->sub.unk_00;
        sub[1] = sp->unk_04;
        sub[2] = sp->unk_08;
        r4 = p->sfield;
        a = 0;
        b = 0;
        func_0204f818(&a, &b, sub);
        func_02087e88(r6, 1);
        func_02087e80(r6, ((PStruct *) obj)->sfield);
        func_0203acd8();
        func_020a18f4();
        func_020b63f4(func_020b5e10(), 0xc, sub, 0x00800000, r4, 2, 2);
        func_ov048_022635f4(obj, 3);
    }
    return 1;
}

int func_ov048_02262954(void)
{
    return 1;
}

int func_ov048_022628b8(struct UnkStruct_022628b8_3 *self)
{
    struct UnkStruct_022628b8_2 *t = func_020682e0(0);
    if (t->type == 5) {
        void *obj;
        struct UnkStruct_022628b8 *p;
        int vec[3];
        int a, b;
        int short_val;

        obj = (void *) func_020860cc((int) func_0208602c());

        p = (struct UnkStruct_022628b8 *) func_020961a8(4);
        {
            int *vp = p->vec;
            vec[0] = vp[0];
            vec[1] = vp[1];
            vec[2] = vp[2];
        }
        short_val = p->s;

        a = 0;
        b = 0;
        func_0204f818(&a, &b, vec);

        func_02087e88((int) obj, 2);
        func_02087e80((int) obj, self->s);

        func_020b5f84(func_020b5e10(), 0xc, vec, 0x00800000, short_val, a, b);

        func_0203acd8();
        func_020a18d0();
        func_020b6434(func_020b5e10(), 0x2e, 2, 3);

        func_ov048_022635f4((void *) self, 3);
    }
    return 1;
}

int func_ov048_022628b4(void)
{
    return 1;
}

int func_ov048_02262880(void *arg)
{
    UnkStruct_02262880 *p;
    int x;

    p = (UnkStruct_02262880 *) func_020682e0(0);
    if (p->unk_04 == 5) {
        func_020a193c();
        x = func_020b5e10();
        func_020b6434(x, 0x2e, 2, 3);
        func_ov048_022635f4(arg, 3);
    }
    return 1;
}

int func_ov048_0226287c(void)
{
    return 1;
}
