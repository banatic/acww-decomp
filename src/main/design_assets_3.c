/* design_assets_3: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020726b8 @ 0x020726b8, 0xc4 bytes, Thumb
 * func_02072638 @ 0x02072638, 0x80 bytes, Thumb
 * func_02072630 @ 0x02072630, 0x8 bytes, Thumb
 * func_02072628 @ 0x02072628, 0x8 bytes, Thumb
 * func_0207261c @ 0x0207261c, 0xc bytes, Thumb
 * func_02072614 @ 0x02072614, 0x8 bytes, Thumb
 * func_02072600 @ 0x02072600, 0x14 bytes, Thumb
 * func_020725f0 @ 0x020725f0, 0x10 bytes, Thumb
 * func_020725ec @ 0x020725ec, 0x2 bytes, Thumb
 * func_020725b4 @ 0x020725b4, 0x38 bytes, Thumb
 * func_02072594 @ 0x02072594, 0x1e bytes, Thumb
 * func_02072588 @ 0x02072588, 0xc bytes, Thumb
 * func_02072578 @ 0x02072578, 0x10 bytes, Thumb
 * func_02072574 @ 0x02072574, 0x2 bytes, Thumb
 * func_0207252c @ 0x0207252c, 0x48 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x38];
} ElemA;

typedef struct {
    unsigned char pad_00[0x2c4];
} ElemB;

struct UnkStruct_02072600 {
    int count;
    int data[16];
};

typedef struct {
    unsigned char *ptr;
    unsigned char *array[16];
} UnkStruct_020725b4;

extern void func_02072808(void *);
extern void func_020723a8(void *self);
extern void *data_021fbe94;
extern int func_020e9948(void *heap, int size);
extern int data_021d0484;
extern int data_021d047c;
extern int data_021d0470;
extern int data_021d0480;
extern void func_0203d228(void *p);
extern void *func_020578ec(void *p);
extern void func_020723a0(void *receiver);
extern void func_020e993c(void *heap, void *p);
extern int func_02072380(int, int, int);
extern int func_02072370(int, unsigned int);
extern int data_021d0504;
extern void *func_02064b18(void *arg);
extern unsigned char data_020e1838[];
extern void func_020e9898(void *param1);
extern int data_021d054c[4][8];
extern int data_021d04e4[8];

void func_020725b4(UnkStruct_020725b4 *param);
void func_02072594(void *param1);
unsigned int func_02072588(unsigned int *base, unsigned int index);
void func_0207252c(void *receiver);

void func_020726b8(void *self)
{
    void *heap;
    void *p1, *p2;
    ElemB *e1;
    ElemA *e2;
    unsigned int i;

    func_02072808(self);
    func_020725b4((UnkStruct_020725b4 *) ((char *) self + 4));
    func_020723a8(self);

    heap = data_021fbe94;

    p1 = (void *) func_020e9948(heap, 0x1620);
    data_021d0484 = (int) p1;

    p2 = (void *) func_020e9948(heap, 0x1c0);
    data_021d047c = (int) p2;

    e1 = (ElemB *) data_021d0484;
    e2 = (ElemA *) p2;
    for (i = 0; i < 8; i++) {
        if (e1 != 0) {
            func_0203d228(e1);
        }
        if (e2 != 0) {
            func_020578ec(e2);
        }
        e1 = (ElemB *) ((char *) e1 + 0x2c4);
        e2 = (ElemA *) ((char *) e2 + 0x38);
    }

    p1 = (void *) func_020e9948(heap, 0x1620);
    data_021d0470 = (int) p1;

    p2 = (void *) func_020e9948(heap, 0x1c0);
    data_021d0480 = (int) p2;

    e1 = (ElemB *) data_021d0470;
    e2 = (ElemA *) p2;
    for (i = 0; i < 8; i++) {
        if (e1 != 0) {
            func_0203d228(e1);
        }
        if (e2 != 0) {
            func_020578ec(e2);
        }
        e1 = (ElemB *) ((char *) e1 + 0x2c4);
        e2 = (ElemA *) ((char *) e2 + 0x38);
    }
}

void func_02072638(void *p)
{
    void *heap;

    func_02072594((char *) p + 4);
    func_020723a0(p);
    heap = data_021fbe94;
    if ((*(void **) &data_021d0484) != 0) {
        func_020e993c(heap, (*(void **) &data_021d0484));
        (*(void **) &data_021d0484) = 0;
    }
    if ((*(void **) &data_021d047c) != 0) {
        func_020e993c(heap, (*(void **) &data_021d047c));
        (*(void **) &data_021d047c) = 0;
    }
    if ((*(void **) &data_021d0470) != 0) {
        func_020e993c(heap, (*(void **) &data_021d0470));
        (*(void **) &data_021d0470) = 0;
    }
    if ((*(void **) &data_021d0480) != 0) {
        func_020e993c(heap, (*(void **) &data_021d0480));
        (*(void **) &data_021d0480) = 0;
    }
}

int func_02072630(int argument0, int argument1, int argument2)
{
    return func_02072380((int) argument0, (int) argument1, (int) argument2);
}

int func_02072628(int argument0, unsigned int argument1)
{
    return func_02072370((int) argument0, (unsigned int) argument1);
}

unsigned int func_0207261c(int a, unsigned int argument1)
{
    return func_02072588((unsigned int *) (a + 4), (unsigned int) argument1);
}

int func_02072614(void)
{
    return (int) &data_021d0504;
}

void func_02072600(struct UnkStruct_02072600 *p)
{
    unsigned int i;
    p->count = 0;
    i = 0;
    do {
        p->data[i] = 0;
        i++;
    } while (i < 16);
}

void *func_020725f0(void *arg)
{
    void *tmp = arg;
    func_02072600((struct UnkStruct_02072600 *) arg);
    return tmp;
}

void func_020725ec(void *receiver) {}

void func_020725b4(UnkStruct_020725b4 *param)
{
    if (param->ptr == 0) {
        param->ptr = func_02064b18((void *) data_020e1838);
        if (param->ptr != 0) {
            unsigned int i;
            for (i = 0; i < 16; i++) {
                param->array[i] = param->ptr + (i << 5);
            }
        }
    }
}

void func_02072594(void *param1)
{
    void *ptr;
    void *local;

    ptr = param1;
    if (*((unsigned int *) ptr) != 0) {
        func_020e9898(*((void **) ptr));
        *((unsigned int *) ptr) = 0;
    }
    func_02072600((struct UnkStruct_02072600 *) ptr);
}

unsigned int func_02072588(unsigned int *base, unsigned int index)
{
    return *(base + (index & 0xF) + 1);
}

int func_02072578(int a)
{
    func_0207252c((void *) a);
    return a;
}

void func_02072574(void *receiver) {}

void func_0207252c(void *receiver)
{
    unsigned char i, j, k;
    k = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 8; j++) {
            data_021d054c[i][j] = k;
        }
    }
    for (k = 0; k < 8; k++) {
        data_021d04e4[k] = 0;
    }
}
