/* villager_talk_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201d6b8 @ 0x0201d6b8, 0x64 bytes, Thumb
 * func_0201d630 @ 0x0201d630, 0x88 bytes, Thumb
 */

typedef struct {
    int a;
    int b;
} Pair;

typedef struct {
    char pad_00[0x124];
    unsigned short lockB;
    char pad_126[0x19c - 0x124 - 2];
    unsigned short lockA;
} UnkStruct_0201d630;

extern int func_02015330(void *self, void *ctx, int a, int b, int c);
extern void func_0207df18(void *a, void *b);
extern void func_02081ac0(void *a, void *b);
extern void func_02068440(void *a);
extern void *func_020984e8(void);
extern void *func_02099734(int);
extern int func_02099e9c(void *ptr);
extern int func_02098f0c(void *a, void *lockAddr, int n, int flag);
extern int func_020996ac(void *a);
extern int func_0203cd2c(int lockID, void *lockp, void *ctrlFuncp, int flag);
extern int func_020154b4(void *self, void *lockAddr, int a, int b, void *c);
extern Pair data_020d9038;
extern void func_0202dbf0(void *self, Pair p);

void func_0201d6b8(void *selfv)
{
    unsigned char *self = (unsigned char *) selfv;
    void *ptr;
    void *val;

    ptr = *(void **) (self + 0x100);
    val = *(void **) ((unsigned char *) ptr + 0x830);

    func_02015330(self, self + 0x124, 0, 5, 0);

    if (val != 0) {
        if (*(unsigned short *) (self + 0x124) != 0xfff1) {
            func_0207df18(val, self + 0x124);
            if (*(void **) (self + 0x12c) != 0) {
                func_02081ac0(*(void **) (self + 0x12c), self + 0x124);
            }
        }
    }
    func_02068440(*(void **) (self + 0x40));
}

int func_0201d630(UnkStruct_0201d630 *self)
{
    void *r4;
    void *r6;
    int ret;

    if (self->lockA == 0xfff1) {
        goto fail;
    }
    if (self->lockB == 0xfff1) {
        goto fail;
    }

    r4 = func_020984e8();
    r6 = func_02099734((int) r4);

    ret = func_02099e9c(&self->lockB);
    if (ret < 0) {
        goto fail;
    }

    func_02098f0c(r6, &self->lockA, ret, 0);
    func_0203cd2c(func_020996ac(r4), &self->lockA, 0, 1);
    func_020154b4(self, &self->lockA, 0, 5, 0);
    func_0202dbf0(self, data_020d9038);
    return 1;

fail:
    return 0;
}
