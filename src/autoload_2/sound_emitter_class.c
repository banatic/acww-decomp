/* sound_emitter_class: 6 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f5484 @ 0x020f5484, 0xd8 bytes, ARM
 * func_020f545c @ 0x020f545c, 0x28 bytes, ARM
 * func_020f5430 @ 0x020f5430, 0x2c bytes, ARM
 * func_020f5400 @ 0x020f5400, 0x30 bytes, ARM
 * func_020f53c8 @ 0x020f53c8, 0x38 bytes, ARM
 * func_020f539c @ 0x020f539c, 0x2c bytes, ARM
 */

typedef struct {
    unsigned char pad_00[0x3f];
    unsigned char flags;
} S020f5484;

struct UnkStruct_020f5430 {
    int *unk_00;
    char pad_04[0x3a];
    unsigned char unk_3E;
};

struct UnkStruct_020f5400 {
    void *volatile unk_00;
};

struct UnkStruct_020f539c {
    int *ptr;
    char pad_04[0x3a];
    unsigned char flag;
};

extern int data_021fd1bc;
extern int func_020f1d3c(void *addr, int arg);
extern int func_020f5748(int, int, int, int);
extern void *func_020f560c(void *);
extern void func_020f5914(struct UnkStruct_020f5400 *obj);
extern unsigned char data_020d8414[];
extern unsigned char data_0213f058[];
extern void func_020edb3c(void *p);
extern int data_0213f090;
extern void func_020f5970(struct UnkStruct_020f539c *);

unsigned int func_020f5484(S020f5484 *p, unsigned int val)
{
    int s = func_020f1d3c(&data_021fd1bc, 4);
    unsigned char f = p->flags;
    int mask2 = f & 2;
    int mask4 = f & 4;

    if (f & 1) {
        if (s == 0 && mask2 == 0 && mask4 == 0) {
            val = (unsigned short) (val + 2);
            p->flags = f | 2;
        } else {
            p->flags &= ~2;
        }
    } else {
        if (s == 0 && mask2 == 0 && mask4 == 0) {
            val = (unsigned short) (val + 3);
            p->flags = f | 4;
        } else {
            p->flags &= ~4;
            val = (unsigned short) (val + 1);
        }
    }
    p->flags ^= 1;
    return val;
}

int func_020f545c(int arg1, unsigned int value, unsigned int flag)
{
    return func_020f5748(arg1, func_020f5484((S020f5484 *) ((void *) arg1), value), 0x7f, 0);
}

void *func_020f5430(struct UnkStruct_020f5430 *this)
{
    func_020f560c(this);
    this->unk_00 = ((int *) data_0213f058);
    this->unk_3E = 0x63;
    return this;
}

void *func_020f5400(struct UnkStruct_020f5400 *obj)
{
    obj->unk_00 = (void *) data_0213f058;
    obj->unk_00 = (void *) data_020d8414;
    func_020f5914(obj);
    return obj;
}

void *func_020f53c8(void *p)
{
    *(volatile unsigned int *) p = (unsigned int) data_0213f058;
    *(volatile unsigned int *) p = (unsigned int) data_020d8414;
    func_020f5914((struct UnkStruct_020f5400 *) p);
    func_020edb3c(p);
    return p;
}

struct UnkStruct_020f539c *func_020f539c(struct UnkStruct_020f539c *obj)
{
    func_020f5970(obj);
    obj->ptr = &data_0213f090;
    obj->flag = 2;
    return obj;
}
