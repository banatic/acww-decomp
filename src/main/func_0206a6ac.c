/* func_0206a6ac @ 0x0206a6ac, 0xe4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct SelfType {
    char pad_00[0x24];
    void *unk_24;
    char pad_28[8];
    int unk_30;
    char pad_34[4];
    int unk_38;
} SelfType;

extern void *func_0206837c(void *);
extern void *func_020ab550(void *, int);
extern void func_020ab5e4(void *);
extern int func_020ab794(void *);
extern int func_020ab798(void *);
extern int func_020a8460(void *, int, int, int, int, int, int, int, int, int, int);
extern void func_020a93e8(void *, int);
extern void func_020ab4bc(void *, int);
extern void func_020a9dc8(void *, void *);
extern void func_020a9d24(void *);

void func_0206a6ac(SelfType *self)
{
    void *list;
    void *e0, *e1, *e2, *e3, *e4;
    int a0, b0, a1, b1, a2, b2, a3, b3, a4, b4;
    int ret;

    list = func_0206837c(self->unk_24);
    e0 = func_020ab550(list, 0);
    e1 = func_020ab550(list, 1);
    e2 = func_020ab550(list, 2);
    e3 = func_020ab550(list, 3);
    e4 = func_020ab550(list, 4);
    func_020ab5e4(list);

    a0 = func_020ab794(e0);
    b0 = func_020ab798(e0);
    a1 = func_020ab794(e1);
    b1 = func_020ab798(e1);
    a2 = func_020ab794(e2);
    b2 = func_020ab798(e2);
    a3 = func_020ab794(e3);
    b3 = func_020ab798(e3);
    a4 = func_020ab794(e4);
    b4 = func_020ab798(e4);

    ret = func_020a8460(&self->unk_38, a0, b0, a1, b1, a2, b2, a3, b3, a4, b4);
    func_020a93e8(self, ret);
    func_020ab4bc(list, 5);
    func_020a9dc8((char *) self->unk_24 + 0xb4, list);
    func_020a9d24((char *) self->unk_24 + 0xb4);
    self->unk_30 = 5;
}
