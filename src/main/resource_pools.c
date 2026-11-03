/* resource_pools: 29 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02078c88 @ 0x02078c88, 0x28 bytes, Thumb
 * func_02078c78 @ 0x02078c78, 0x10 bytes, Thumb
 * func_02078c74 @ 0x02078c74, 0x2 bytes, Thumb
 * func_02078c4c @ 0x02078c4c, 0x28 bytes, Thumb
 * func_02078c34 @ 0x02078c34, 0x18 bytes, Thumb
 * func_02078c2c @ 0x02078c2c, 0x6 bytes, Thumb
 * func_02078bfc @ 0x02078bfc, 0x30 bytes, Thumb
 * func_02078bc0 @ 0x02078bc0, 0x3c bytes, Thumb
 * func_02078bb0 @ 0x02078bb0, 0x10 bytes, Thumb
 * func_02078bac @ 0x02078bac, 0x2 bytes, Thumb
 * func_02078b84 @ 0x02078b84, 0x28 bytes, Thumb
 * func_02078b6c @ 0x02078b6c, 0x18 bytes, Thumb
 * func_02078b64 @ 0x02078b64, 0x6 bytes, Thumb
 * func_02078b2c @ 0x02078b2c, 0x38 bytes, Thumb
 * func_02078af0 @ 0x02078af0, 0x3c bytes, Thumb
 * func_02078ae8 @ 0x02078ae8, 0x6 bytes, Thumb
 * func_02078ae4 @ 0x02078ae4, 0x2 bytes, Thumb
 * func_02078adc @ 0x02078adc, 0x8 bytes, Thumb
 * func_02078ad8 @ 0x02078ad8, 0x4 bytes, Thumb
 * func_02078ab0 @ 0x02078ab0, 0x28 bytes, Thumb
 * func_02078a9c @ 0x02078a9c, 0x14 bytes, Thumb
 * func_02078a94 @ 0x02078a94, 0x6 bytes, Thumb
 * func_02078a90 @ 0x02078a90, 0x2 bytes, Thumb
 * func_02078a70 @ 0x02078a70, 0x20 bytes, Thumb
 * func_02078a5c @ 0x02078a5c, 0x14 bytes, Thumb
 * func_02078a54 @ 0x02078a54, 0x6 bytes, Thumb
 * func_02078a50 @ 0x02078a50, 0x2 bytes, Thumb
 * func_02078a30 @ 0x02078a30, 0x20 bytes, Thumb
 * func_02078a1c @ 0x02078a1c, 0x14 bytes, Thumb
 */

typedef struct {
    unsigned long a[64];
} UnkStruct_02078c2c;

typedef struct {
    unsigned long a[64];
} UnkStruct_02078b64;

typedef struct {
    unsigned long unk_00;
} UnkStruct_02078ae8;

typedef struct {
    unsigned long unk_00;
} UnkStruct_02078a94;

typedef struct {
    unsigned long unk_00;
} UnkStruct_02078a54;

extern void func_020e9b9c(void *ptr);
extern unsigned char data_021c9ac4[];
extern unsigned int func_0205c300(int);
extern int func_020e9abc(unsigned int param);
extern unsigned char data_021d1310[];
extern void func_0205c2e4(void);
extern void *data_021c9ac0;
extern int func_020ea0e0(unsigned int, void *);
extern unsigned int func_0205c2a0(int);
extern unsigned char data_021c9abc[];
extern unsigned char data_021d12a4[];
extern void func_0205c284(void);
extern int func_02085f08(void);
extern int func_02078d1c(int *p, int value);
extern int func_02064af4(int a, int b, int c);
extern int data_021d12dc;

void func_02078bfc(int *arr);
void func_02078bc0(void *param);
void func_02078b2c(unsigned int *arr);
void func_02078af0(int *arr);
void func_02078ad8(int *p0, int p1);

void func_02078c88(void *param)
{
    void **global_ptr = *(void ***) data_021c9ac4;
    int i;
    void *ptr;

    for (i = 0; i < 5; i++) {
        ((void **) param)[i] = 0;
    }

    if (global_ptr != 0) {
        func_020e9b9c(global_ptr);
    }
}

void func_02078c78(int *p)
{
    int i;
    for (i = 0; i < 8; i++) {
        p[i] = 0;
    }
}

void func_02078c74(void *object) {}

void func_02078c4c(int argument0)
{
    func_0205c300((int) argument0);
    func_02078bfc((int *) ((unsigned int) data_021d1310));
    if ((*(unsigned int *) &data_021c9ac0)) {
        func_020e9abc((*(unsigned int *) &data_021c9ac0));
    }
}

void func_02078c34(void)
{
    func_02078bc0((void *) data_021d1310);
    func_0205c2e4();
}

unsigned long func_02078c2c(UnkStruct_02078c2c *p, int i)
{
    return p->a[i];
}

void func_02078bfc(int *arr)
{
    void *p = data_021c9ac0;
    int i;
    for (i = 0; i < 8; i++) {
        arr[i] = func_020ea0e0(0x7ac, p);
    }
}

void func_02078bc0(void *param)
{
    void **r5;
    void **r7;
    int r4;
    void **r6;
    void *r0;
    void *sp_val;

    r7 = param;
    r5 = data_021c9ac0;
    r4 = 0;
    sp_val = 0;
    while (r4 < 8) {
        r6 = r7 + r4;
        r0 = r7[r4];
        if (r0 != 0) {
            func_020e9b9c(r0);
            r6[0] = sp_val;
        }
        r4++;
    }
    if (r5 != 0) {
        func_020e9b9c(r5);
    }
}

void func_02078bb0(int *a)
{
    int i;
    int v;

    for (i = 0, v = i; i < 4; i++) {
        a[i] = v;
    }
}

void func_02078bac(void *object) {}

void func_02078b84(int argument0)
{
    void *ptr;
    void *ptr2;

    func_0205c2a0((int) argument0);
    func_02078b2c((unsigned int *) ((void *) data_021d12a4));
    ptr = (void *) data_021c9abc;
    ptr2 = *(void **) ptr;
    if (ptr2 != 0) {
        func_020e9abc((unsigned int) ptr2);
    }
}

void func_02078b6c(void)
{
    (((int) (func_02078af0((int *) ((void *) data_021d12a4)), (void *) data_021d12a4)), func_0205c284());
}

unsigned long func_02078b64(UnkStruct_02078b64 *p, int i)
{
    return p->a[i];
}

void func_02078b2c(unsigned int *arr)
{
    unsigned int *ptr;
    int count;
    int i;
    ptr = (*(unsigned int * *) data_021c9abc);
    count = func_02085f08();
    for (i = 0; i < count; i++) {
        arr[i] = (unsigned int) func_020ea0e0(0x7AC, (void *) ptr);
    }
}

void func_02078af0(int *arr)
{
    int local = 0;
    int r5 = (*(int *) data_021c9abc);
    int i;
    for (i = 0; i < 4; i++) {
        if (arr[i] != 0) {
            func_020e9b9c((void *) arr[i]);
            arr[i] = local;
        }
    }
    if (r5 != 0) {
        func_020e9b9c((void *) r5);
    }
}

void func_02078ae8(UnkStruct_02078ae8 *p)
{
    p->unk_00 = 5;
}

void func_02078ae4(void *receiver) {}

void func_02078adc(int *argument0, int argument1)
{
    func_02078ad8((int *) argument0, (int) argument1);
}

void func_02078ad8(int *p0, int p1)
{
    p0[0] = p1;
}

void func_02078ab0(int *a, int b)
{
    int result;
    result = func_02078d1c(&data_021d12dc, *a);
    func_02064af4(b, result, 0x2f88);
}

int func_02078a9c(int *arg)
{
    return func_02078d1c(&data_021d12dc, *arg);
}

void func_02078a94(UnkStruct_02078a94 *p)
{
    p->unk_00 = 8;
}

void func_02078a90(void *receiver) {}

void func_02078a70(int *out, int value)
{
    func_020e9b9c((void *) func_02078c2c((UnkStruct_02078c2c *) ((void *) data_021d1310), value));
    *out = value;
}

unsigned long func_02078a5c(void *param)
{
    void *addr = (void *) data_021d1310;
    return func_02078c2c((UnkStruct_02078c2c *) addr, (int) (*(void **) param));
}

void func_02078a54(UnkStruct_02078a54 *p)
{
    p->unk_00 = 4;
}

void func_02078a50(void *receiver) {}

void func_02078a30(int *param0, int param1)
{
    func_020e9b9c((void *) ((int) func_02078b64((UnkStruct_02078b64 *) (((char *) data_021d12a4)), param1)));
    *param0 = param1;
}

unsigned long func_02078a1c(void *param)
{
    void *r1;
    void *r0;
    void *r3;

    r1 = param;
    r0 = (void *) data_021d12a4;
    r1 = *(void **) r1;
    r3 = (void *) (unsigned long (*)(void *, void *)) func_02078b64;
    return func_02078b64((UnkStruct_02078b64 *) r0, (int) r1);
}
