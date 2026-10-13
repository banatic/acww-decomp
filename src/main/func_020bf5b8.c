/* func_020bf5b8 @ 0x020bf5b8, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: the empty if keeps self->idx loaded before the table address; the plain expression loads the address first */

extern struct UnkStruct_020bf5b8 {
    int a;
    int b;
    int c;
} data_020e7880[];

extern void func_0208a1f0(void *dst, struct UnkStruct_020bf5b8 *e);
extern void func_0208a1ec(void *dst, int c);
extern void func_0208a144(void *dst);

struct UnkStruct_020bf5b8_2 {
    char pad_00[0xC];
    int idx;
    int sub;
};

void func_020bf5b8(struct UnkStruct_020bf5b8_2 *self)
{
    int idx;
    struct UnkStruct_020bf5b8 *e;

    idx = self->idx;
    if ((idx && idx) && idx) {
    }
    e = &data_020e7880[idx];
    func_0208a1f0(&self->sub, e);
    func_0208a1ec(&self->sub, e->c);
    func_0208a144(&self->sub);
}
