/* sound_point: 4 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020f4eec @ 0x020f4eec, 0x58 bytes, ARM
 * func_020f4d4c @ 0x020f4d4c, 0x1a0 bytes, ARM
 * func_020f4d00 @ 0x020f4d00, 0x4c bytes, ARM
 * func_020f4c70 @ 0x020f4c70, 0x90 bytes, ARM
 */

struct Node {
    unsigned char pad_00[0x1b];
    unsigned char unk_1B;
};

struct UnkStruct_020f4d4c_5 {
    unsigned char pad_00[8];
    unsigned short unk_08;
};

struct UnkStruct_020f4d4c {
    unsigned char pad_00[4];
    signed char unk_04;
};

struct UnkStruct_020f4d4c_2 {
    unsigned char pad_00[0x2c];
    struct UnkStruct_020f4d4c *q;
};

struct UnkStruct_020f4d4c_3 {
    unsigned char pad_00[0x38];
    unsigned short unk_38;
};

struct UnkStruct_020f4d4c_4 {
    struct UnkStruct_020f4d4c_3 *z;
};

extern unsigned long func_020efc18(const unsigned long *stream);
extern int func_020efc2c(int a, int b);
extern void func_020efc44(int a, int b);
extern struct UnkStruct_020f4d4c_2 data_021fd1bc;
extern int func_020f5134(struct Node *);
extern void func_020f5178(struct Node *);
extern void func_020efc38(struct UnkStruct_020f4d4c_5 *, struct Node *);
extern int func_020efc10(struct UnkStruct_020f4d4c_5 *);
extern void func_020f51c4(void *node);
extern void *func_020efc20(struct UnkStruct_020f4d4c_5 *, int);
extern void NNS_SndPlayerStopSeqBySeqArcIdx(int, int, int);
extern unsigned char data_021fd1f8[];
extern int func_020eedb8(int a, int b, void *c);
extern int func_020f5e50(void *a, int b);
extern int func_020f5e24(int argument0);
extern int func_020f5c64(void *a, int b);
extern void NNS_SndPlayerSetVolume(void *a, int b);
extern void func_0210b634(void *a, int b, int c);

void func_020f4eec(int a, int b)
{
    int found = 1;
    int v;
    v = func_020efc18((const unsigned long *) a);
    while (v != 0) {
        if (v == b) {
            found = 0;
            break;
        }
        v = func_020efc2c(a, v);
    }
    if (found == 0) {
        return;
    }
    func_020efc44(a, b);
}

// List teardown and re-emit. The object address is cast from an integer, so the null check stays.
void func_020f4d4c(struct UnkStruct_020f4d4c_5 *self)
{
    struct Node *e;
    struct Node *p;
    int n;
    int i;
    int t;
    struct UnkStruct_020f4d4c_4 *r;
    unsigned short h;
    struct Node *e2;
    int j;

    e = (struct Node *) func_020efc18((const unsigned long *) self);
    while (e != 0) {
        if (func_020f5134(e)) {
            func_020f5178(e);
            func_020efc38(self, e);
        }
        e = (struct Node *) func_020efc2c((int) self, (int) e);
    }
    n = self->unk_08;
    if (n == 1) {
        func_020f51c4((void *) func_020efc10(self));
    } else if (n == 2) {
        t = func_020efc10(self);
        func_020f51c4((void *) t);
        func_020f51c4(func_020efc20(self, t));
    } else if (n > 2) {
        e2 = (struct Node *) func_020efc18((const unsigned long *) self);
        n = n - 2;
        j = 0;
        if (n > 0) {
            do {
                func_020f5178(e2);
                e2 = (struct Node *) func_020efc2c((int) self, (int) e2);
                j++;
            } while (j < n);
        }
        t = func_020efc10(self);
        func_020f51c4((void *) t);
        func_020f51c4(func_020efc20(self, t));
    }
    p = (struct Node *) func_020efc18((const unsigned long *) self);
    while (p != 0) {
        p->unk_1B = 0;
        p = (struct Node *) func_020efc2c((int) self, (int) p);
    }
    if (data_021fd1bc.q->unk_04 != 0xa) {
        return;
    }
    r = (struct UnkStruct_020f4d4c_4 *) data_021fd1f8;
    if (r == 0) {
        return;
    }
    h = r->z->unk_38;
    if (h >= 0xb0 && h <= 0xf5) {
        return;
    }
    NNS_SndPlayerStopSeqBySeqArcIdx(1, 0x107, 5);
}

unsigned int func_020f4d00(void *stream, unsigned int len)
{
    unsigned int ret = func_020efc18((const unsigned long *) stream);

    if (ret == 0) {
        return ret;
    }

    do {
        if (ret == len) {
            func_020efc38((struct UnkStruct_020f4d4c_5 *) stream, (struct Node *) len);
        }
        ret = (unsigned int) func_020efc2c((int) stream, ret);
    } while (ret != 0);

    return ret;
}

void func_020f4c70(unsigned char *p0, int p1, void *p2)
{
    int rem;
    int saved;
    int b;

    rem = p1 % 1000;
    func_020eedb8((unsigned short) rem, 1, p0 + 12);

    saved = func_020f5e24((int) func_020f5e50(p2, 0));
    b = func_020f5c64(p2, 0);
    NNS_SndPlayerSetVolume(p0 + 12, saved);
    func_0210b634(p0 + 12, 0xff, b);
}
