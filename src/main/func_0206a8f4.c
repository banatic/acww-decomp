/* func_0206a8f4 @ 0x0206a8f4, 0x82 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x24];
    char *unk_24;
    char pad_28[0x08];
    int unk_30;
    char pad_34[0x04];
    char unk_38;
} UnkStruct_0206a8f4;

extern void *func_0206837c(void *);
extern void *func_020ab550(void *, int);
extern void func_020ab5e4(void *);
extern int func_020ab794(void *);
extern int func_020ab798(void *);
extern int func_020a85c4(void *, int, int, int, int);
extern void func_020a93e8(UnkStruct_0206a8f4 *, int);
extern void func_020ab4bc(void *, int);
extern void func_020a9dc8(void *, void *);
extern void func_020a9d24(void *);

void func_0206a8f4(UnkStruct_0206a8f4 *p)
{
    void *obj, *a, *b;
    int x, y, u, v, r;
    obj = func_0206837c(p->unk_24);
    a = func_020ab550(obj, 0);
    b = func_020ab550(obj, 1);
    func_020ab5e4(obj);
    x = func_020ab794(a);
    y = func_020ab798(a);
    u = func_020ab794(b);
    v = func_020ab798(b);
    r = func_020a85c4(&p->unk_38, x, y, u, v);
    func_020a93e8(p, r);
    func_020ab4bc(obj, 2);
    func_020a9dc8(p->unk_24 + 0xb4, obj);
    func_020a9d24(p->unk_24 + 0xb4);
    p->unk_30 = 5;
}
