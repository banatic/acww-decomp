/* heap_14: 10 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020ea450 @ 0x020ea450, 0x3c bytes, ARM
 * func_020ea41c @ 0x020ea41c, 0x34 bytes, ARM
 * func_020ea3f0 @ 0x020ea3f0, 0x2c bytes, ARM
 * func_020ea3e0 @ 0x020ea3e0, 0x10 bytes, ARM
 * func_020ea3bc @ 0x020ea3bc, 0x24 bytes, ARM
 * func_020ea3ac @ 0x020ea3ac, 0x10 bytes, ARM
 * func_020ea388 @ 0x020ea388, 0x24 bytes, ARM
 * func_020ea35c @ 0x020ea35c, 0x2c bytes, ARM
 * func_020ea338 @ 0x020ea338, 0x24 bytes, ARM
 * func_020ea30c @ 0x020ea30c, 0x2c bytes, ARM
 */

struct UnkStruct_020ea450 {
    unsigned int *unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    volatile unsigned int unk_10;
};

typedef struct {
    void *unk_00;
    char pad_04[16];
    unsigned int unk_14;
} UnkStruct_020ea3f0;

extern void OS_InitMutex(void *mutex);
extern int data_0213e608;
extern char data_0213e660;
extern char data_0213e5b0;
extern void func_020edb3c(void *);

void func_020ea450(struct UnkStruct_020ea450 *self, unsigned int a, unsigned int b, unsigned int c)
{
    self->unk_00 = ((unsigned int *) &data_0213e660);
    self->unk_04 = a;
    self->unk_08 = b;
    self->unk_0C = c;
    self->unk_10 = 0;
    self->unk_10 = 0x4000;
}

void *func_020ea41c(void *obj, int a, int b, int c, int d)
{
    func_020ea450((struct UnkStruct_020ea450 *) obj, a, b, c);
    *(void **) obj = (void *) ((unsigned char *) &data_0213e5b0);
    *((int *) ((char *) obj + 0x14)) = d;
    OS_InitMutex((char *) obj + 0x18);
    return obj;
}

void *func_020ea3f0(UnkStruct_020ea3f0 *p, int a, int b, int c, unsigned int d)
{
    func_020ea450((struct UnkStruct_020ea450 *) p, a, b, c);
    p->unk_00 = (void *) &data_0213e608;
    p->unk_14 = d;
    return p;
}

void func_020ea3e0(void *out)
{
    *(void **) out = &data_0213e660;
}

void *func_020ea3bc(void *p)
{
    *(void **) p = (void *) &data_0213e660;
    func_020edb3c((void *) ((int) p));
    return p;
}

void func_020ea3ac(int *out)
{
    *out = (int) ((int *) &data_0213e660);
}

void *func_020ea388(void *self)
{
    *(void **) self = &data_0213e5b0;
    func_020ea3ac((int *) self);
    return self;
}

void *func_020ea35c(void *obj)
{
    *(void **) obj = &data_0213e5b0;
    func_020ea3ac((int *) obj);
    func_020edb3c(obj);
    return obj;
}

void *func_020ea338(void *obj)
{
    *(void **) obj = &data_0213e608;
    func_020ea3ac((int *) obj);
    return obj;
}

void *func_020ea30c(void *obj)
{
    *(void **) obj = (void *) ((char *) &data_0213e608);
    func_020ea3ac((int *) obj);
    func_020edb3c(obj);
    return obj;
}
