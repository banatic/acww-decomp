/* transition_mark_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208fae8 @ 0x0208fae8, 0x3c bytes, Thumb
 * func_0208fac4 @ 0x0208fac4, 0x24 bytes, Thumb
 * func_0208fa9c @ 0x0208fa9c, 0x28 bytes, Thumb
 * func_0208fa1c @ 0x0208fa1c, 0x80 bytes, Thumb
 */

struct UnkStruct_0208fae8 {
    void *vtable;
    char pad_04[8];
    char sub[20];
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
    char unk_38;
    char unk_39;
};

typedef struct {
    unsigned char pad_00[0x38];
    unsigned char unk_38;
    unsigned char unk_39;
} UnkStruct_0208fa1c;

extern void func_0208af30(struct UnkStruct_0208fae8 *);
extern void func_0208a1f8(void *);
extern char data_020e2400[];
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);
extern void func_020edb3c(void *);
extern int func_0208aef0(void *p);
extern int func_0208aeec(void *p);
extern void *func_0208a1d0(void *p);
extern void func_02088df8(int a, void *b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l);

struct UnkStruct_0208fae8 *func_0208fae8(struct UnkStruct_0208fae8 *this)
{
    func_0208af30(this);
    this->vtable = data_020e2400;
    func_0208a1f8(&this->sub);
    this->unk_20 = 0;
    this->unk_24 = 0;
    this->unk_28 = 0;
    this->unk_2C = 0;
    this->unk_30 = 0;
    this->unk_34 = 0;
    this->unk_38 = 0;
    this->unk_39 = 0;
    return this;
}

void *func_0208fac4(void *p)
{
    *(unsigned int *) p = (unsigned int) ((unsigned char *) data_020e2400);
    func_0208a1f4((char *) p + 0xC);
    func_0208af00(p);
    return p;
}

void *func_0208fa9c(void *self)
{
    *(void **) self = (void *) ((char *) data_020e2400);
    func_0208a1f4((char *) self + 12);
    func_0208af00(self);
    func_020edb3c(self);
    return self;
}

void func_0208fa1c(UnkStruct_0208fa1c *param)
{
    if (param->unk_38 != 0 && param->unk_39 == 0) {
        int ret1;
        int ret2;
        char *p;
        void *ret3;

        ret1 = func_0208aef0(param);
        ret2 = func_0208aeec(param);
        p = (char *) param + 0xc;
        ret3 = func_0208a1d0(p);

        func_02088df8(0, ret3, ret1, ret2, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        func_02088df8(0, ret3, ret1, ret2, -1, -1, 0x1000, 0x1000, 0, 2, 0, 0);
    }
}
