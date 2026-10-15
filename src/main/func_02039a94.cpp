/* func_02039a94 @ 0x02039a94, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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
    virtual unsigned int m3()
    {
        return 0;
    }
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
