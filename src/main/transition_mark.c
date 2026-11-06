/* transition_mark: 26 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208f97c @ 0x0208f97c, 0x3c bytes, Thumb
 * func_0208f95c @ 0x0208f95c, 0x20 bytes, Thumb
 * func_0208f930 @ 0x0208f930, 0x2c bytes, Thumb
 * func_0208f8fc @ 0x0208f8fc, 0x34 bytes, Thumb
 * func_0208f8f0 @ 0x0208f8f0, 0xc bytes, Thumb
 * func_0208f8e0 @ 0x0208f8e0, 0x10 bytes, Thumb
 * func_0208f8d0 @ 0x0208f8d0, 0x10 bytes, Thumb
 * func_0208f8c0 @ 0x0208f8c0, 0x10 bytes, Thumb
 * func_0208f8b0 @ 0x0208f8b0, 0x10 bytes, Thumb
 * func_0208f88c @ 0x0208f88c, 0x24 bytes, Thumb
 * func_0208f884 @ 0x0208f884, 0x8 bytes, Thumb
 * func_0208f874 @ 0x0208f874, 0x10 bytes, Thumb
 * func_0208f864 @ 0x0208f864, 0x10 bytes, Thumb
 * func_0208f858 @ 0x0208f858, 0xc bytes, Thumb
 * func_0208f838 @ 0x0208f838, 0x1e bytes, Thumb
 * func_0208f7f8 @ 0x0208f7f8, 0x40 bytes, Thumb
 * func_0208f748 @ 0x0208f748, 0xb0 bytes, Thumb
 * func_0208f720 @ 0x0208f720, 0x28 bytes, Thumb
 * func_0208f708 @ 0x0208f708, 0x18 bytes, Thumb
 * func_0208f6e8 @ 0x0208f6e8, 0x20 bytes, Thumb
 * func_0208f6c8 @ 0x0208f6c8, 0x20 bytes, Thumb
 * func_0208f6a0 @ 0x0208f6a0, 0x28 bytes, Thumb
 * func_0208f690 @ 0x0208f690, 0x10 bytes, Thumb
 * func_0208f680 @ 0x0208f680, 0x10 bytes, Thumb
 * func_0208f670 @ 0x0208f670, 0x10 bytes, Thumb
 * func_0208f660 @ 0x0208f660, 0x10 bytes, Thumb
 */

typedef struct UnkStruct_0208f95c {
    unsigned char pad_00[0xc];
    unsigned short unk_0C;
} UnkStruct_0208f95c;

typedef struct UnkStruct_0208f95c_2 {
    unsigned char pad_00[0x28];
    unsigned int unk_28;
} UnkStruct_0208f95c_2;

typedef struct UnkStruct_0208f874_2 UnkStruct_0208f874;

typedef void *(*FuncPtr)(UnkStruct_0208f874 *);

struct UnkStruct_0208f874_2 {
    struct _Vtbl *vtbl;
};

struct _Vtbl {
    int unk_00;
    int unk_04;
    int unk_08;
    FuncPtr func;
};

typedef void *(*func_ptr)(void *);

typedef struct {
    unsigned char pad_00[0x28];
    int counter;
    int state;
    unsigned long long threshold;
    unsigned char flag;
} UnkStruct_0208f748;

extern struct UnkStruct_0208f97c {
    char pad_00[0xc];
    unsigned short unk_0C;
} *data_021f42f4;
extern struct UnkStruct_0208f97c_3 {
    int pad_00;
} *data_020ccf94;
extern int func_02073d90(struct UnkStruct_0208f97c_3 *);
extern unsigned char data_020d0ba4[];
extern unsigned char data_020d0ba8[];
extern void func_02001cf4(int);
extern void func_02001bb4(int);
extern unsigned char data_021d3654[];
extern unsigned char data_021d3674[];
extern void func_02001d1c(int);
extern unsigned long long OS_GetTick(void);
extern void func_02001ba4(int);
extern void func_0208a1f0(void *a, void *b);
extern void func_0208a1ec(void *a, int b);
extern void *func_0208a144(void *a);
extern unsigned char data_020d71f4;
extern int func_020edf70(int);
extern void *func_020ee660(void *p);
extern unsigned char data_020da13c[];
extern unsigned char data_020e241c[];
extern void func_020ee62c(void *a);
extern void func_020edf54(volatile int *);

void func_0208f88c(void *arg0);
void func_0208f884(unsigned char *argument0);
void *func_0208f874(UnkStruct_0208f874 *self);
void *func_0208f864(void *obj);
void func_0208f858(unsigned char *ptr);
void func_0208f7f8(void *r4);
void func_0208f720(void *s);
void *func_0208f6e8(void *p);

void func_0208f97c(int param0)
{
    unsigned short f;
    int r;

    f = data_021f42f4->unk_0C;
    r = func_02073d90(data_020ccf94);
    if (f != 5 && r != 0) {
        (*(struct UnkStruct_0208f97c_2 {
            char pad_00[0x24];
            int unk_24;
        } *) data_021d3654)
            .unk_24 = data_020d0ba4[param0];
    }
}

void func_0208f95c(int param)
{
    if ((*(UnkStruct_0208f95c **) &data_021f42f4)->unk_0C == 5) {
        return;
    }
    (*(UnkStruct_0208f95c_2 *) data_021d3654).unk_28 = data_020d0ba8[param];
}

void func_0208f930(void)
{
    unsigned int *ptr;
    unsigned char *byte_ptr;

    ptr = (unsigned int *) data_021d3654;
    if (ptr[8] != 0) {
        func_02001cf4(0x10);
        func_02001bb4(4);
    }
    byte_ptr = (unsigned char *) data_021d3674;
    byte_ptr[0x19] = 0;
}

void func_0208f8fc(void)
{
    unsigned int *p;
    unsigned char *q;

    p = (unsigned int *) data_021d3654;
    if (p[8] != 0) {
        func_02001cf4(0x10);
        func_02001d1c(4);
        func_02001bb4(4);
    }
    q = (unsigned char *) data_021d3674;
    q[0x19] = 0;
}

void func_0208f8f0(void)
{
    (*(struct {
        unsigned char pad[0x19];
        unsigned char value;
    } *) data_021d3674)
        .value = 1;
}

void func_0208f8e0(void)
{
    func_0208f88c((void *) data_021d3654);
}

void func_0208f8d0(void)
{
    func_0208f884((unsigned char *) ((void *) data_021d3654));
}

void func_0208f8c0(void)
{
    func_0208f874((UnkStruct_0208f874 *) ((void *) data_021d3654));
}

void func_0208f8b0(void)
{
    func_0208f864((void *) data_021d3654);
}

void func_0208f88c(void *arg0)
{
    func_0208f720(arg0);
    *(unsigned int *) ((char *) arg0 + 0x24) = 0;
    *(unsigned int *) ((char *) arg0 + 0x28) = 0;
    *(unsigned int *) ((char *) arg0 + 0x2c) = 0;
    *(unsigned int *) ((char *) arg0 + 0x30) = 0;
    *(unsigned int *) ((char *) arg0 + 0x34) = 0;
    *(unsigned char *) ((char *) arg0 + 0x38) = 0;
    *(unsigned char *) ((char *) arg0 + 0x39) = 0;
}

void func_0208f884(unsigned char *argument0)
{
    func_0208f858((unsigned char *) argument0);
}

void *func_0208f874(UnkStruct_0208f874 *self)
{
    return self->vtbl->func(self);
}

void *func_0208f864(void *obj)
{
    func_ptr *vtbl;
    vtbl = *(func_ptr **) obj;
    return vtbl[2](obj);
}

void func_0208f858(unsigned char *ptr)
{
    *(unsigned int *) (ptr + 0x20) = 0;
    *(unsigned int *) (ptr + 0x24) = 0;
    ptr[0x38] = 0;
}

void func_0208f838(void *param1)
{
    int temp;

    temp = *(int *) ((char *) param1 + 0x24);
    if (temp > 0) {
        temp--;
        *(int *) ((char *) param1 + 0x24) = temp;
        if (*(int *) ((char *) param1 + 0x24) > 0) {
            return;
        }
        func_0208f7f8(param1);
    }
}

void func_0208f7f8(void *r4)
{
    unsigned long long v;
    unsigned char *p;
    int r5;

    *(int *) ((char *) r4 + 0x20) = 1;
    *(int *) ((char *) r4 + 0x28) = 0;
    func_02001cf4(0x10);
    func_02001bb4(4);
    v = OS_GetTick();
    r5 = 1;
    *(int *) ((char *) r4 + 0x2c) = r5;
    *(unsigned long long *) ((char *) r4 + 0x30) = v + 0x1991bULL;
    p = (unsigned char *) r4 + 0x38;
    *p = (unsigned char) r5;
}

void func_0208f748(UnkStruct_0208f748 *self)
{
    unsigned long long t = OS_GetTick();
    if (t < self->threshold) {
        goto skip_switch;
    }
    if (self->state == 0) {
        t += 0x1991b;
        self->threshold = t;
        self->flag = 1;
        self->state = 1;
    } else if (self->state == 1) {
        t += 0x1991b;
        self->threshold = t;
        self->flag = 0;
        self->state = 2;
    } else if (self->state == 2) {
        t += 0x1991b;
        self->threshold = t;
        self->flag = 1;
        self->state = 3;
    } else if (self->state == 3) {
        t += 0x4cb51;
        self->threshold = t;
        self->flag = 0;
        self->state = 0;
    }
skip_switch:
    if (self->counter > 0) {
        self->counter--;
        if (self->counter <= 0) {
            func_02001ba4(4);
            func_0208f858((unsigned char *) self);
        }
    }
}

void func_0208f720(void *s)
{
    func_0208a1f0((char *) s + 0xc, &data_020d71f4);
    func_0208a1ec((char *) s + 0xc, 1);
    func_0208a144((char *) s + 0xc);
}

void func_0208f708(void)
{
    int result;

    result = func_020edf70(0x50);
    if (result != 0) {
        func_0208f6e8((void *) result);
    }
}

void *func_0208f6e8(void *p)
{
    volatile void **ptr = (volatile void **) p;
    func_020ee660(p);
    *ptr = (void *) data_020da13c;
    *ptr = (void *) data_020e241c;
    return p;
}

void *func_0208f6c8(void *arg)
{
    *(void **) arg = (void *) data_020e241c;
    *(void **) arg = (void *) data_020da13c;
    func_020ee62c(arg);
    return arg;
}

volatile int *func_0208f6a0(volatile int *p)
{
    *p = (unsigned int) data_020e241c;
    *p = (unsigned int) data_020da13c;
    func_020ee62c((void *) p);
    func_020edf54(p);
    return p;
}

int func_0208f690(void)
{
    func_0208f8e0();
    return 1;
}

int func_0208f680(void)
{
    func_0208f8d0();
    return 1;
}

int func_0208f670(void)
{
    func_0208f8c0();
    return 1;
}

int func_0208f660(void)
{
    func_0208f8b0();
    return 1;
}
