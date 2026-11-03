/* star_designer_input_3: 8 functions, module ov129
 * mwccarm 1.2/base -O4,s
 * func_ov129_0229c644 @ 0x0229c644, 0x40 bytes, Thumb
 * func_ov129_0229c610 @ 0x0229c610, 0x34 bytes, Thumb
 * func_ov129_0229c574 @ 0x0229c574, 0x9c bytes, Thumb
 * func_ov129_0229c548 @ 0x0229c548, 0x2c bytes, Thumb
 * func_ov129_0229c520 @ 0x0229c520, 0x26 bytes, Thumb
 * func_ov129_0229c4b8 @ 0x0229c4b8, 0x68 bytes, Thumb
 * func_ov129_0229c468 @ 0x0229c468, 0x50 bytes, Thumb
 * func_ov129_0229c418 @ 0x0229c418, 0x50 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xae];
    unsigned char key;
} func_ov129_0229c574_self;

struct func_ov129_0229c548_ctx {
    unsigned char pad_00[0xae];
    unsigned char unk_AE;
};

typedef struct {
    char pad_00[0xae];
    unsigned char flag;
} UnkStruct_0229c520;

typedef struct {
    char pad_00[0x98];
    int unk_98;
    unsigned char pad_9C[0xae - 0x98 - 4];
    unsigned char unk_AE;
    char pad_AF[0x1d4 - 0xae - 1];
    char unk_1D4;
} UnkStruct_0229c418;

extern int func_ov129_0229b7ec(void *a, int b);
extern void func_0200467c(int cmd);
extern void *func_ov002_0220a720(void *a, int b);
extern void func_ov002_02208090(void *a, int b);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov002_0220b9b8(char *dst, char *src, int size, int mode);
extern void func_0208e5c4(char *ptr);
extern int func_ov002_022088ac(void *);
extern int func_ov002_0220889c(void *);
extern int func_ov002_022088cc(void *);
extern int func_ov002_022088bc(void *);
extern unsigned char data_ov129_0229dae4[];
extern unsigned char data_ov129_0229daf4[];
extern unsigned char data_ov129_0229dafc[];
extern unsigned char data_ov129_0229daec[];
extern void func_ov129_0229c348(char *p);
extern void func_ov002_0220a0b4(char *p, int a, int b);
extern void func_ov002_0220a374(char *p, int n);
extern int func_ov002_0220a768(void *p, int a);
extern const unsigned char data_ov129_0229db40[];
extern int func_ov002_0220a72c(void *addr, int param);
extern const unsigned char data_ov129_0229db48[];

int func_ov129_0229c468(void *p);
int func_ov129_0229c418(UnkStruct_0229c418 *self);

void func_ov129_0229c644(void *p)
{
    if (func_ov129_0229b7ec(p, 4) != 0) {
        func_0200467c(0x29);
    } else {
        func_0200467c(0x2a);
    }
    func_ov002_0220a720((char *) p + 0x1d4, 4);
    func_ov002_02208090(p, 8);
    func_ov002_02208098((void *) (p), 0xa);
}

void func_ov129_0229c610(char *self, char value)
{
    char local = value;
    func_ov002_0220b9b8(self + 0xb8, &local, 1, 0);
    func_ov002_02208098((void *) (self), 14);
    func_0208e5c4(self + 0x3a0);
}

int func_ov129_0229c574(func_ov129_0229c574_self *self, void *arg)
{
    unsigned char old;
    unsigned char idx;

    old = self->key;

    if (func_ov002_022088ac(arg)) {
        idx = self->key;
        self->key = data_ov129_0229dae4[idx];
    } else if (func_ov002_0220889c(arg)) {
        idx = self->key;
        self->key = data_ov129_0229daf4[idx];
    } else if (func_ov002_022088cc(arg)) {
        idx = self->key;
        self->key = data_ov129_0229dafc[idx];
    } else if (func_ov002_022088bc(arg)) {
        idx = self->key;
        self->key = data_ov129_0229daec[idx];
    }

    return old != self->key;
}

int func_ov129_0229c548(struct func_ov129_0229c548_ctx *arg)
{
    if (func_ov129_0229b7ec(arg, 2) != 0) {
        return 1;
    }
    if ((unsigned char) (arg->unk_AE + 0xfd) <= 1) {
        return 0;
    }
    return 1;
}

int func_ov129_0229c520(UnkStruct_0229c520 *arg)
{
    if (func_ov129_0229b7ec((void *) arg, 2) != 0) {
        return 0;
    }
    if (arg->flag == 4) {
        return 1;
    }
    return 0;
}

void func_ov129_0229c4b8(char *p)
{
    int a = func_ov129_0229c468((void *) p);
    int b = func_ov129_0229c418((UnkStruct_0229c418 *) p);
    func_ov002_0220a0b4(p + 0x3a0, a, b);
    if (func_ov129_0229c548((struct func_ov129_0229c548_ctx *) p)) {
        func_ov002_0220a374(p + 0x3a0, 1);
    } else if (func_ov129_0229c520((UnkStruct_0229c520 *) p)) {
        func_ov002_0220a374(p + 0x3a0, 7);
    } else {
        func_ov002_0220a374(p + 0x3a0, 0xd);
    }
    func_ov129_0229c348(p);
}

int func_ov129_0229c468(void *p)
{
    unsigned char b;
    if (func_ov129_0229b7ec(p, 2)) {
        return *(int *) ((char *) p + 0x94);
    }
    b = *((unsigned char *) p + 0xae);
    switch (b) {
        case 4:
            return func_ov002_0220a768((char *) p + 0x1d4, 6);
        case 5:
            return func_ov002_0220a768((char *) p + 0x1d4, 5);
        default:
            return data_ov129_0229db40[b];
    }
}

int func_ov129_0229c418(UnkStruct_0229c418 *self)
{
    if (func_ov129_0229b7ec(self, 2) != 0) {
        return self->unk_98;
    } else {
        unsigned char b = self->unk_AE;
        switch (b) {
            case 4:
                return func_ov002_0220a72c(&self->unk_1D4, 6);
            case 5:
                return func_ov002_0220a72c(&self->unk_1D4, 5);
            default:
                return data_ov129_0229db48[b];
        }
    }
}
