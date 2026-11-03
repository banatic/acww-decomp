/* quick_message_8: 21 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203a454 @ 0x0203a454, 0x18 bytes, Thumb
 * func_0203a448 @ 0x0203a448, 0xc bytes, Thumb
 * func_0203a430 @ 0x0203a430, 0x18 bytes, Thumb
 * func_0203a424 @ 0x0203a424, 0xc bytes, Thumb
 * func_0203a404 @ 0x0203a404, 0x20 bytes, Thumb
 * func_0203a3ec @ 0x0203a3ec, 0x18 bytes, Thumb
 * func_0203a3cc @ 0x0203a3cc, 0x20 bytes, Thumb
 * func_0203a3c8 @ 0x0203a3c8, 0x4 bytes, Thumb
 * func_0203a3c4 @ 0x0203a3c4, 0x4 bytes, Thumb
 * func_0203a3a4 @ 0x0203a3a4, 0x20 bytes, Thumb
 * func_0203a38c @ 0x0203a38c, 0x18 bytes, Thumb
 * func_0203a36c @ 0x0203a36c, 0x20 bytes, Thumb
 * func_0203a368 @ 0x0203a368, 0x4 bytes, Thumb
 * func_0203a364 @ 0x0203a364, 0x4 bytes, Thumb
 * func_0203a344 @ 0x0203a344, 0x20 bytes, Thumb
 * func_0203a330 @ 0x0203a330, 0x14 bytes, Thumb
 * func_0203a310 @ 0x0203a310, 0x20 bytes, Thumb
 * func_0203a30c @ 0x0203a30c, 0x4 bytes, Thumb
 * func_0203a308 @ 0x0203a308, 0x4 bytes, Thumb
 * func_0203a2f0 @ 0x0203a2f0, 0x18 bytes, Thumb
 * func_0203a2dc @ 0x0203a2dc, 0x14 bytes, Thumb
 */

struct func_0203a404_struct {
    void *unk_00;
};

typedef struct {
    void *unk_00;
    char pad_04[12];
    int unk_10;
    int unk_14;
} UnkStruct_0203a3a4;

typedef struct {
    unsigned int unk_00;
} UnkStruct_0203a36c;

extern void func_020edb3c(void *);
extern unsigned char data_020da6c4[];
extern char data_020da6dc;
extern void *func_020a8cac(void *ptr);
extern void func_020a8c1c(void *ptr);
extern void *func_020a8c38(void *self);
extern unsigned char data_020da640[];
extern void *func_020a88ec(void *);
extern unsigned char data_020da628[];
extern void *func_020a887c(void *arg);
extern unsigned char data_020da5f8;
extern void func_02051ad8(void *);
extern unsigned char data_020da610[];

void *func_0203a454(void *p)
{
    void *x;
    x = (void *) data_020da6c4;
    *(void **) p = x;
    func_020edb3c(p);
    return p;
}

void func_0203a448(int **p)
{
    *p = ((int *) data_020da6c4);
}

void *func_0203a430(void *arg)
{
    *(unsigned int *) arg = (unsigned int) ((unsigned int *) &data_020da6dc);
    func_020edb3c(arg);
    return arg;
}

void func_0203a424(char **ptr)
{
    *ptr = &data_020da6dc;
}

struct func_0203a404_struct *func_0203a404(struct func_0203a404_struct *self)
{
    func_020a8cac(self);
    self->unk_00 = ((char *) data_020da640);
    func_020a8c1c(self);
    return self;
}

void *func_0203a3ec(void *self)
{
    *(void **) self = ((char *) data_020da640);
    func_020a8c38(self);
    return self;
}

void *func_0203a3cc(void *ptr)
{
    *(void **) ptr = (void *) data_020da640;
    func_020a8c38(ptr);
    func_020edb3c(ptr);
    return ptr;
}

int func_0203a3c8(void)
{
    return 34;
}

int func_0203a3c4(int p0)
{
    return ((int) (p0) + (18));
}

UnkStruct_0203a3a4 *func_0203a3a4(UnkStruct_0203a3a4 *p, int a, int b)
{
    func_020a88ec(p);
    p->unk_00 = data_020da628;
    p->unk_10 = a;
    p->unk_14 = b;
    return p;
}

void *func_0203a38c(void *arg)
{
    *((void **) arg) = ((char *) data_020da628);
    func_020a887c(arg);
    return arg;
}

UnkStruct_0203a36c *func_0203a36c(UnkStruct_0203a36c *obj)
{
    obj->unk_00 = (unsigned int) ((unsigned int *) data_020da628);
    func_020a887c((void *) obj);
    func_020edb3c((void *) obj);
    return obj;
}

int func_0203a368(int *p0)
{
    return p0[5];
}

int func_0203a364(int *p0)
{
    return p0[4];
}

void *func_0203a344(void *arg)
{
    *(unsigned char *volatile *) arg = ((unsigned char *) &data_020da6dc);
    *(unsigned char *volatile *) arg = &data_020da5f8;
    func_02051ad8(arg);
    return arg;
}

void func_0203a330(volatile unsigned int *ptr)
{
    *ptr = (unsigned int) ((char *) &data_020da5f8);
    *ptr = (unsigned int) &data_020da6dc;
}

void *func_0203a310(void *p)
{
    volatile int *vp;
    vp = (volatile int *) p;
    *vp = (int) ((int *) &data_020da5f8);
    *vp = (int) ((int *) &data_020da6dc);
    func_020edb3c(p);
    return p;
}

int func_0203a30c(void)
{
    return 14;
}

int func_0203a308(int p0)
{
    return ((int) (p0) + (4));
}

void func_0203a2f0(unsigned int *mem, unsigned int a, unsigned int b)
{
    *(volatile unsigned int *) mem = (unsigned int) data_020da6c4;
    *(volatile unsigned int *) mem = (unsigned int) data_020da610;
    mem[1] = a;
    mem[2] = b;
}

void func_0203a2dc(volatile unsigned int *p)
{
    *p = (unsigned int) ((int *) data_020da610);
    *p = (unsigned int) ((int *) data_020da6c4);
}
