/* func_020f4d4c @ 0x020f4d4c, 0x1a0 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

// List teardown and re-emit. The object address is cast from an integer, so the null check stays.
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

extern struct UnkStruct_020f4d4c_2 data_021fd1bc;

extern struct Node *func_020efc18(struct UnkStruct_020f4d4c_5 *);
extern int func_020f5134(struct Node *);
extern void func_020f5178(struct Node *);
extern void func_020efc38(struct UnkStruct_020f4d4c_5 *, struct Node *);
extern struct Node *func_020efc2c(struct UnkStruct_020f4d4c_5 *, struct Node *);
extern int func_020efc10(struct UnkStruct_020f4d4c_5 *);
extern void func_020f51c4(void *node);
extern void *func_020efc20(struct UnkStruct_020f4d4c_5 *, int);
extern void NNS_SndPlayerStopSeqBySeqArcIdx(int, int, int);

extern unsigned char data_021fd1f8[];

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

    e = func_020efc18(self);
    while (e != 0) {
        if (func_020f5134(e)) {
            func_020f5178(e);
            func_020efc38(self, e);
        }
        e = func_020efc2c(self, e);
    }
    n = self->unk_08;
    if (n == 1) {
        func_020f51c4((void *) func_020efc10(self));
    } else if (n == 2) {
        t = func_020efc10(self);
        func_020f51c4((void *) t);
        func_020f51c4(func_020efc20(self, t));
    } else if (n > 2) {
        e2 = func_020efc18(self);
        n = n - 2;
        j = 0;
        if (n > 0) {
            do {
                func_020f5178(e2);
                e2 = func_020efc2c(self, e2);
                j++;
            } while (j < n);
        }
        t = func_020efc10(self);
        func_020f51c4((void *) t);
        func_020f51c4(func_020efc20(self, t));
    }
    p = func_020efc18(self);
    while (p != 0) {
        p->unk_1B = 0;
        p = func_020efc2c(self, p);
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
