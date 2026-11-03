/* activity_talk: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a261c @ 0x020a261c, 0x34 bytes, Thumb
 * func_020a25e8 @ 0x020a25e8, 0x34 bytes, Thumb
 * func_020a25cc @ 0x020a25cc, 0x1a bytes, Thumb
 * func_020a259c @ 0x020a259c, 0x2e bytes, Thumb
 * func_020a2584 @ 0x020a2584, 0x18 bytes, Thumb
 * func_020a256c @ 0x020a256c, 0x18 bytes, Thumb
 * func_020a254c @ 0x020a254c, 0x20 bytes, Thumb
 * func_020a2548 @ 0x020a2548, 0x4 bytes, Thumb
 * func_020a24d8 @ 0x020a24d8, 0x70 bytes, Thumb
 * func_020a24d4 @ 0x020a24d4, 0x2 bytes, Thumb
 */

struct UnkStruct_020a259c {
    int unk_00;
    int unk_04;
};

typedef struct {
    void *vtbl;
} UnkStruct_020a2584;

typedef struct {
    char pad_00[0x1e];
    unsigned char unk_1E;
    char pad_1F[0x48 - 0x1f];
    int unk_48;
} Struct020a24d8;

extern int func_020682e0(int);
extern void func_02068358(int);
extern void func_02068434(int);
extern void func_0206844c(int, char *, char *);
extern char data_020e3c40[];
extern void func_02068364(struct UnkStruct_020a259c *p, int b);
extern void *func_02066a30(UnkStruct_020a2584 *self);
extern char data_020e3b38;
extern void *func_02066994(void *ptr);
extern void func_020edb3c(void *);
extern void func_02068440(int);
extern void func_020a4e94(int, int);
extern int data_021f43e8;

void func_020a261c(void *object)
{
    int a;
    char c;
    a = func_020682e0(0);
    func_02068358(a);
    func_02068434(a);
    c = 10;
    func_0206844c(a, &c, data_020e3c40);
}

void func_020a25e8(void *object)
{
    int a;
    char b;
    a = func_020682e0(0);
    func_02068358(a);
    func_02068434(a);
    b = 0x0b;
    func_0206844c(a, &b, ((char *) data_020e3c40));
}

void func_020a25cc(void *receiver)
{
    int a;
    a = func_020682e0(0);
    func_02068358(a);
    func_02068434(a);
}

int func_020a259c(int a, int b)
{
    struct UnkStruct_020a259c *ptr;
    ptr = (struct UnkStruct_020a259c *) func_020682e0(0);
    if (ptr->unk_04 == 2) {
        if (b != 0) {
            func_02068364(ptr, 1);
        } else {
            func_02068364(ptr, 0);
        }
        return 1;
    } else {
        return 0;
    }
}

UnkStruct_020a2584 *func_020a2584(UnkStruct_020a2584 *self)
{
    func_02066a30(self);
    self->vtbl = &data_020e3b38;
    return self;
}

void *func_020a256c(void *ptr)
{
    *(void **) ptr = &data_020e3b38;
    func_02066994(ptr);
    return ptr;
}

void *func_020a254c(void *this)
{
    *(void **) this = &data_020e3b38;
    func_02066994(this);
    func_020edb3c(this);
    return this;
}

void func_020a2548(int *p0, int p1)
{
    p0[18] = p1;
}

void func_020a24d8(Struct020a24d8 *self)
{
    int ret = func_020682e0(0);

    switch (self->unk_1E) {
        case 10:
            func_02068440(ret);
            break;
        case 8:
            func_0206844c(ret, (char *) (&data_021f43e8), 0);
            break;
        case 39:
            func_0206844c(ret, (char *) (&data_021f43e8), 0);
            break;
        case 38:
            func_02068440(ret);
            func_020a4e94(self->unk_48, 0x1e);
            break;
        case 105:
            func_0206844c(ret, (char *) (&data_021f43e8), 0);
            break;
    }
}

void func_020a24d4(void) {}
