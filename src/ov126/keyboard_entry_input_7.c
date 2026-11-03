/* keyboard_entry_input_7: 8 functions, module ov126
 * mwccarm 1.2/base -O4,s
 * func_ov126_022a0ae0 @ 0x022a0ae0, 0xb0 bytes, Thumb
 * func_ov126_022a0a90 @ 0x022a0a90, 0x50 bytes, Thumb
 * func_ov126_022a0a50 @ 0x022a0a50, 0x40 bytes, Thumb
 * func_ov126_022a0978 @ 0x022a0978, 0xd8 bytes, Thumb
 * func_ov126_022a0934 @ 0x022a0934, 0x44 bytes, Thumb
 * func_ov126_022a0924 @ 0x022a0924, 0xe bytes, Thumb
 * func_ov126_022a0904 @ 0x022a0904, 0x20 bytes, Thumb
 * func_ov126_022a08c4 @ 0x022a08c4, 0x40 bytes, Thumb
 */

struct UnkStruct_022a0a50 {
    char pad_00[0xad];
    unsigned char unk_AD;
};

typedef struct UnkStruct_022a0978_2 {
    char pad_00[0xa6];
    unsigned char unk_A6;
    char pad_A7;
    unsigned char unk_A8;
    char pad_A9[4];
    unsigned char unk_AD;
    char pad_AE[0x19c - 0xae];
    char sub_19c;
    char pad_19D[0x3dc4 - 0x19d];
    char sub_3dc4;
    char pad_3DC5[0x4248 - 0x3dc5];
    char sub_4248;
} UnkStruct_022a0978;

struct UnkStruct_022a0934 {
    unsigned char pad_00[0x98];
    unsigned int unk_98;
    unsigned int unk_9C;
    unsigned char pad_A0[0xab - 0xa0];
    unsigned char unk_AB;
};

struct UnkStruct_022a0904 {
    char pad_00[0xA8];
    unsigned char b;
    char pad_A9[0x419F];
    unsigned short arr[1];
};

struct UnkStruct_022a08c4 {
    char pad_00[0x98];
    int unk_98;
    int unk_9C;
    char pad_A0[0xa8 - 0xa0];
    unsigned char unk_A8;
    char pad_A9[0xab - 0xa9];
    unsigned char unk_AB;
    char pad_AC[0x4248 - 0xac];
    char unk_4248;
};

extern void *func_ov002_0220a720(void *self, int arg);
extern void func_ov126_0229f7b8(void *self, int arg);
extern void func_ov126_0229f7a8(void *self, int arg);
extern int func_ov126_0229f7c8(void *self, int arg);
extern void func_0200467c(int cmd);
extern int func_0206fca4(void);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov002_0220a620(void *p, int n);
extern void func_ov126_022a0110(void *receiver);
extern int func_ov126_0229ffdc(void *p);
extern int func_02051ca8(void *p, int b);
extern void func_ov002_0220a63c(void *p, int a);
extern void func_ov002_0220a658(void *p, int a);
extern void func_ov095_0229ce84(void *p, int a);
extern void func_ov095_0229cef4(void *p, int a);
extern void func_ov095_0229bee4(void *p);
extern void func_ov095_0229bed8(void *receiver, int value);
extern int func_ov126_022a0740(UnkStruct_022a0978 *self);
extern void func_ov126_022a0728(struct UnkStruct_022a0934 *);
extern void func_ov095_0229cd30(void *);
extern int func_02051d08(void *, int);

void func_ov126_022a0924(void *arg0, char arg1);
unsigned short func_ov126_022a0904(struct UnkStruct_022a0904 *s);

void func_ov126_022a0ae0(void *self, int flag)
{
    if (flag == 0) {
        func_ov002_0220a720((char *) self + 0x3dc4, 6);
        if (*(unsigned char *) ((char *) self + 0xad) == 1) {
            func_ov126_0229f7b8(self, 0x40);
        } else {
            func_ov126_0229f7a8(self, 0x40);
        }
    } else {
        func_ov002_0220a720((char *) self + 0x3dc4, 7);
        func_ov126_0229f7b8(self, 0x40);
    }
    if (func_ov126_0229f7c8(self, 0x20) != 0) {
        if (func_ov126_0229f7c8(self, 0x40) != 0) {
            func_0200467c(0x2a);
        } else {
            if (func_0206fca4() == 0x19) {
                func_0200467c(0x27);
            } else {
                func_0200467c(0x29);
            }
        }
    } else {
        if (func_ov126_0229f7c8(self, 0x40) != 0) {
            func_0200467c(0x28);
        } else {
            func_0200467c(0x27);
        }
    }
    *(unsigned char *) ((char *) self + 0x8c) = 3;
    func_ov002_02208098((void *) (self), 0xf);
}

int func_ov126_022a0a90(unsigned char *p)
{
    if (func_ov002_0220a620(p + 0x3dc4, 6) != 0) {
        func_ov126_022a0110((void *) p);
        return 0;
    }
    {
        unsigned char b = p[0xad];
        if (b == 0 || b == 2) {
            func_ov126_0229ffdc(p);
            func_ov126_022a0ae0(p, 0);
            return 1;
        } else {
            func_ov126_022a0110((void *) p);
            return 0;
        }
    }
}

int func_ov126_022a0a50(struct UnkStruct_022a0a50 *s)
{
    switch (s->unk_AD) {
        case 0:
            func_ov126_0229ffdc(s);
            func_ov126_022a0ae0(s, 1);
            return 1;
        case 1:
            func_ov126_0229ffdc(s);
            func_ov126_022a0ae0(s, 0);
            return 1;
        default:
            func_ov126_022a0110(s);
            return 0;
    }
}

void func_ov126_022a0978(UnkStruct_022a0978 *self)
{
    if (self->unk_AD == 0 || self->unk_AD == 2) {
        if (func_02051ca8(&self->sub_4248, self->unk_A6) == 0) {
            func_ov002_0220a658(&self->sub_3dc4, 6);
        } else {
            func_ov002_0220a63c(&self->sub_3dc4, 6);
        }
    }
    func_ov095_0229cef4(&self->sub_19c, 0);
    if (func_ov126_022a0740(self) != 0) {
        func_ov095_0229ce84(&self->sub_19c, 0xb);
    } else {
        func_ov095_0229cef4(&self->sub_19c, 0xb);
    }
    if (func_ov126_0229f7c8((void *) self, 8) != 0) {
        func_ov095_0229ce84(&self->sub_19c, 0xc);
    } else {
        func_ov095_0229cef4(&self->sub_19c, 0xc);
    }
    if (func_ov126_022a0740(self) != 0) {
        func_ov095_0229bee4(&self->sub_19c);
        func_ov095_0229ce84(&self->sub_19c, 6);
    } else {
        if (self->unk_A8 == 0) {
            func_ov095_0229bee4(&self->sub_19c);
        } else {
            int v = (int) func_ov126_022a0904((struct UnkStruct_022a0904 *) self);
            func_ov095_0229bed8(&self->sub_19c, v);
        }
    }
}

void func_ov126_022a0934(struct UnkStruct_022a0934 *p)
{
    func_ov126_0229f7b8((void *) p, 2);
    p->unk_98 = p->unk_AB;
    p->unk_9C = 0x28;
    func_ov126_022a0924((void *) p, 0);
    func_ov126_022a0728(p);
    func_ov095_0229cd30((char *) p + 0x19c);
    func_ov126_022a0978((UnkStruct_022a0978 *) p);
}

void func_ov126_022a0924(void *arg0, char arg1)
{
    ((char *) arg0)[0xa8] = arg1;
    ((char *) arg0)[0xa7] = 0x10;
}

unsigned short func_ov126_022a0904(struct UnkStruct_022a0904 *s)
{
    if (s->b == 0) {
        return 0;
    }
    return s->arr[s->b - 1];
}

void func_ov126_022a08c4(struct UnkStruct_022a08c4 *p)
{
    p->unk_98 = p->unk_AB;
    p->unk_9C = 0x28;
    p->unk_98 += (unsigned char) func_02051d08(&p->unk_4248, p->unk_A8);
}
