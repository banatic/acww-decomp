/* func_0201a1d4 @ 0x0201a1d4, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201a3e8(void *);
extern void **func_02082da8(void **);
extern void func_0205d7b8(void **, void *, int, int);
extern void *func_0205d894(void **);
extern void func_0205678c(void **, void *, int, int, int, int);
extern void func_0201a27c(void *);
extern void func_02056730(void **);

struct UnkStruct_0201a1d4 {
    char pad_00[0x14];
    void *unk_14;
    char pad_18[0x30];
    void *unk_48;
    char pad_48_50[4];
    int unk_50;
    char pad_54[0x24];
    void *unk_78;
};

void func_0201a1d4(struct UnkStruct_0201a1d4 *a, void *b, int c)
{
    void **p;
    void *q;

    if (func_0201a3e8(a) == 0) {
        return;
    }
    p = func_02082da8(&a->unk_14);
    func_0205d7b8(p, b, 1, 0);
    q = func_0205d894(p);
    func_0205678c(&a->unk_48, q, 0, 0, c, 0x1000);
    a->unk_50 = 0;
    a->unk_78 = b;
    func_0201a27c(a);
    func_02056730(&a->unk_48);
}
