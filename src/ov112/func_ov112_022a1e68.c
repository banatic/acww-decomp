/* func_ov112_022a1e68 @ 0x022a1e68, 0xd8 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

typedef void (*Callback)(void);

typedef struct {
    char pad_00[0x24];
} Node;

typedef struct {
    void *vtbl;
} UnkStruct_022a1e68;

extern void *func_ov002_02207f80(int size);
extern void func_ov002_0220830c(void *self);
extern void func_ov002_0220ba24(void *self);
extern void func_020b9cfc(void *self);
extern void func_02138d6c(void *self, int a, int b, Callback cb1, Callback cb2);
extern void func_ov002_0220a5fc(void *self);
extern void func_ov002_0220b008(void *self);
extern void func_ov002_02209ccc(void *self);
extern void func_020780d0(void *self);
extern void func_02078058(void *self);
extern void func_02070be8(void);
extern void func_02070c08(void);
extern char data_ov112_022a20d0;

void *func_ov112_022a1e68(void)
{
    UnkStruct_022a1e68 *self;
    Node *p;
    Node *q;

    self = (UnkStruct_022a1e68 *) func_ov002_02207f80(0x6c6c);
    if (self == 0) {
        goto ret;
    }

    func_ov002_0220830c(self);
    self->vtbl = &data_ov112_022a20d0;
    func_ov002_0220ba24((char *) self + 0x244);

    p = (Node *) ((char *) self + 0x360);
    q = (Node *) ((char *) self + 0x384);
    do {
        func_020b9cfc(p);
        p++;
    } while (p != q);

    p = (Node *) ((char *) q + 0x2308);
    q = (Node *) ((char *) q + 0x2350);
    do {
        func_020b9cfc(p);
        p++;
    } while (p != q);

    func_02138d6c(q, 2, 0x6c, func_02070c08, func_02070be8);
    func_02138d6c((char *) self + 0x3fac, 6, 0x6c, func_02070c08, func_02070be8);
    func_ov002_0220a5fc((char *) self + 0x4234);
    func_ov002_0220b008((char *) self + 0x427c);
    func_ov002_02209ccc((char *) self + 0x4448);
    func_020780d0((char *) self + 0x44ac);
    func_02078058((char *) self + 0x4580);

ret:
    return self;
}
