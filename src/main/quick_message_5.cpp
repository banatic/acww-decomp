/* quick_message_5: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02039a94 @ 0x02039a94, 0x9c bytes, Thumb
 * func_020399e4 @ 0x020399e4, 0xb0 bytes, Thumb
 */

extern "C" void *func_0208a1c8(void *);
extern "C" void *func_0208a1e0(void *, int, int);

class UnkStruct_02039a94 {
  public:
    virtual unsigned int m0()
    {
        return 0;
    }
    virtual unsigned int m1()
    {
        return 0;
    }
    virtual unsigned int m2()
    {
        return 0;
    }
    virtual unsigned int m3();
    unsigned char pad[0x30 - 4];
    unsigned int unk_30;
};

struct Main {
    unsigned char pad_00[0x0c];
    int c;
    unsigned char pad_10[0x1c - 0x10];
    unsigned char arr1[0x30 - 0x1c];
    unsigned char arr2[0x9c - 0x30];
    UnkStruct_02039a94 *a;
    UnkStruct_02039a94 *b;
};

struct UnkStruct_020399e4 {
    char pad_00[0x10];
    int unk_10;
    char pad1[0x18];
    int unk_2C;
    char pad2[8];
    unsigned char unk_38;
    unsigned char unk_39;
    char pad_3A[0x16];
    int unk_50;
    unsigned char unk_54;
    unsigned char unk_55;
    char pad_56[2];
    int unk_58;
};

extern "C" {
extern void *func_020a9034(int, int, int);
extern void func_02051694(UnkStruct_020399e4 *);
extern int data_021c8c9c;
}

struct UnkStruct_020399e4_2 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int v3();
};

struct UnkStruct_020399e4_3 {
    char pad_00[0xc];
    volatile int unk_0C;
    char pad1[0x78];
    UnkStruct_020399e4_2 sub88;
    char pad2[0x10];
    UnkStruct_020399e4 *unk_9C;
};

extern "C" void func_02039a94(Main *self)
{
    if (self->a != 0) {
        unsigned int size = self->a->m3();
        int r4 = (size + 7) >> 3;
        unsigned int r6 = (r4 << 3) - size;
        int bound = *((int *) func_0208a1c8(self->arr1) + 1);
        int lim = bound - 1;
        int t = r4 - 1;
        int r1;
        if (t < 0) {
            r1 = 0;
        } else if (t > lim) {
            r1 = lim;
        } else {
            r1 = t;
        }
        func_0208a1e0(self->arr1, r1, 0);
        self->a->unk_30 = r6;
    }
    unsigned int size2 = self->b->m3();
    int r4_2 = (size2 + 7) >> 3;
    unsigned int r6_2 = size2;
    int bound2 = *((int *) func_0208a1c8(self->arr2) + 1);
    int lim2 = bound2 - 1;
    int t2 = r4_2 - 1;
    int r1_2;
    if (t2 < 0) {
        r1_2 = 0;
    } else if (t2 > lim2) {
        r1_2 = lim2;
    } else {
        r1_2 = t2;
    }
    func_0208a1e0(self->arr2, r1_2, 0);
    if (self->c == 0 && self->b != 0) {
        self->b->unk_30 = ((r4_2 << 3) - r6_2) >> 1;
    }
}

extern "C" void func_020399e4(UnkStruct_020399e4_3 *obj)
{
    UnkStruct_020399e4 *q;

    if (obj->unk_0C == 0) {
        return;
    }
    if (obj->unk_9C != 0) {
        return;
    }
    obj->unk_9C = (UnkStruct_020399e4 *) func_020a9034(obj->unk_0C * 8 + 0x1c0, 8, 2);
    if (obj->unk_9C == 0) {
        return;
    }
    obj->unk_9C->unk_2C = 4;
    q = obj->unk_9C;
    q->unk_10 = obj->sub88.v3();
    if (data_021c8c9c == 0) {
        obj->unk_9C->unk_50 = 3;
    } else {
        obj->unk_9C->unk_50 = 2;
    }
    obj->unk_9C->unk_58 = 1;
    obj->unk_9C->unk_55 = 1;
    obj->unk_9C->unk_39 = 0xe;
    obj->unk_9C->unk_38 = 0xd;
    func_02051694(obj->unk_9C);
}
