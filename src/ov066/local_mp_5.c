/* local_mp_5: 5 functions, module ov066
 * mwccarm 1.2/base -O4,p
 * func_ov066_022699ec @ 0x022699ec, 0x28 bytes, ARM
 * func_ov066_022699cc @ 0x022699cc, 0x20 bytes, ARM
 * func_ov066_0226997c @ 0x0226997c, 0x50 bytes, ARM
 * func_ov066_02269934 @ 0x02269934, 0x48 bytes, ARM
 * func_ov066_022698ec @ 0x022698ec, 0x48 bytes, ARM
 */

typedef struct UnkStruct_0226997c UnkStruct_0226997c;

typedef struct UnkStruct_0226997c_2 UnkStruct_0226997c_2;

typedef struct {
    void *unk_00;
    UnkStruct_0226997c *unk_04;
} UnkStruct_0226997c_3;

struct UnkStruct_0226997c {
    void *unk_00;
    UnkStruct_0226997c_2 *unk_04;
};

struct UnkStruct_0226997c_2 {
    unsigned char pad_00[0x17e];
    unsigned short value;
};

typedef struct {
    char pad_00[0xb4];
    int (*func)(void);
} UnkStruct_02269934;

typedef struct UnkStruct_022698ec {
    unsigned char pad_00[0xb0];
    int (*unk_B0)(int a, int b, int c, int d);
} UnkStruct_022698ec;

extern unsigned int data_ov066_0226bdf8;
extern struct UnkStruct_022699cc {
    char pad_00[0x1e];
    unsigned short unk_1E;
} *data_ov066_0226bdf4;
extern int func_ov066_0226760c(void);
extern void DC_InvalidateRange(void *addr, int n);

unsigned int func_ov066_022699ec(void)
{
    unsigned int next = data_ov066_0226bdf8 * 0x5eedf715u + 0x1b0cb173u;
    data_ov066_0226bdf8 = next;
    return next;
}

int func_ov066_022699cc(void)
{
    return data_ov066_0226bdf4 ? data_ov066_0226bdf4->unk_1E : 0xffff;
}

unsigned short func_ov066_0226997c(void)
{
    UnkStruct_0226997c_3 *a;
    UnkStruct_0226997c *b;
    UnkStruct_0226997c_2 *c;

    if (func_ov066_0226760c() != 10) {
        return 0;
    }

    a = (*(UnkStruct_0226997c_3 * *) &data_ov066_0226bdf4);
    b = a->unk_04;
    c = b->unk_04;

    DC_InvalidateRange(&c->value, 2);

    return c->value;
}

int func_ov066_02269934(void)
{
    int (*fn)(void);
    UnkStruct_02269934 *obj = (*(UnkStruct_02269934 * *) &data_ov066_0226bdf4);

    if (obj != 0 && (fn = obj->func) != 0) {
        return fn();
    }
    return 0;
}

int func_ov066_022698ec(int a, int b, int c, int d)
{
    UnkStruct_022698ec *p = (*(UnkStruct_022698ec * *) &data_ov066_0226bdf4);
    if (p && p->unk_B0) {
        return p->unk_B0(a, b, c, d);
    }
    return 0;
}
