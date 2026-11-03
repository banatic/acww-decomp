/* held_item_4: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205f024 @ 0x0205f024, 0x4c bytes, Thumb
 * func_0205f00c @ 0x0205f00c, 0x18 bytes, Thumb
 * func_0205eff4 @ 0x0205eff4, 0x18 bytes, Thumb
 * func_0205efd4 @ 0x0205efd4, 0x20 bytes, Thumb
 * func_0205efac @ 0x0205efac, 0x28 bytes, Thumb
 * func_0205ef90 @ 0x0205ef90, 0x1a bytes, Thumb
 * func_0205ef5c @ 0x0205ef5c, 0x34 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xd];
    unsigned char unk_0D;
} UnkStruct_0205f024;

struct UnkStruct_0205ef90 {
    char pad_00[8];
    char unk_08;
    char pad_09[31];
    char unk_28;
};

typedef struct UnkStruct_0205ef5c {
    char pad_00[0x2c];
    void *ptr;
} UnkStruct_0205ef5c;

typedef struct UnkStruct_0205ef5c_2 {
    char pad_00[4];
    UnkStruct_0205ef5c *inner;
    char pad_08[0x24 - 8];
    void (*callback)(void *p);
    char pad_28[0x92 - 0x28];
    unsigned char unk_92;
} UnkStruct_0205ef5c_2;

extern UnkStruct_0205f024 *func_0205f140(void *a, int);
extern unsigned long func_0205f2f0(void *a, void *b);
extern int func_021077e8(unsigned int *);
extern int func_020b9eec(UnkStruct_0205f024 *e, int v, int k);
extern void func_020565ec(void *ptr);
extern char data_020dd754;
extern void *func_02056578(void *arg);
void func_020edb3c(void *obj);
extern void func_020606c0(void *);
extern void func_020606bc(void *ptr);
extern char data_021ca16c[];
extern int func_0205f130(const char *str, unsigned char c);
extern void func_02054d60(int result, UnkStruct_0205ef5c_2 *p);
extern void func_0205ef28(void *p);

int func_0205f024(void *a, void *b)
{
    UnkStruct_0205f024 *e = func_0205f140(a, (int) b);
    unsigned int k = e->unk_0D;
    unsigned int t1;
    unsigned int t2;
    if (k == 2) {
        t1 = 1;
    } else {
        t1 = 0;
    }
    if (t1 > 0) {
        return 1;
    }
    if (k == 1) {
        t2 = 1;
    } else {
        t2 = 0;
    }
    if (t2 == 0) {
        func_020b9eec(e, func_021077e8((unsigned int *) func_0205f2f0(a, b)), 1);
    }
    return 0;
}

void *func_0205f00c(void *obj)
{
    func_020565ec(obj);
    *(void **) obj = (void *) ((int *) &data_020dd754);
    return obj;
}

void *func_0205eff4(void *arg)
{
    *(void **) arg = &data_020dd754;
    func_02056578(arg);
    return arg;
}

void *func_0205efd4(void *obj)
{
    *(void **) obj = &data_020dd754;
    func_02056578(obj);
    func_020edb3c(obj);
    return obj;
}

void *func_0205efac(void *self)
{
    func_0205f00c((char *) self + 8);
    func_020606c0((char *) self + 0x28);
    *((unsigned char *) self) = 9;
    *((unsigned int *) ((char *) self + 4)) = 0x1000;
    return self;
}

void *func_0205ef90(struct UnkStruct_0205ef90 *arg)
{
    func_020606bc(&arg->unk_28);
    func_0205eff4(&arg->unk_08);
    return arg;
}

void func_0205ef5c(UnkStruct_0205ef5c_2 *p)
{
    if (p->inner->ptr != 0) {
        func_02054d60(func_0205f130(data_021ca16c, *((unsigned char *) p->inner->ptr)), p);
    }
    p->callback = func_0205ef28;
    p->unk_92 = 2;
}
