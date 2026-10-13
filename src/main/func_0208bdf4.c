/* func_0208bdf4 @ 0x0208bdf4, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a1f0(void *ptr, void *arg2);
extern void func_0208a1ec(void *ptr, int arg2);
extern void func_0208a144(void *ptr);
extern char data_020d5c3c;

typedef struct {
    char pad_00[0xc];
    void *child;
    char pad_10[0x10];
    int unk_20;
} UnkStruct_0208bdf4;

void func_0208bdf4(void *p)
{
    UnkStruct_0208bdf4 *self = (UnkStruct_0208bdf4 *) p;

    self->unk_20 = 1;
    func_0208a1f0(&self->child, &data_020d5c3c);
    func_0208a1ec(&self->child, 1);
    func_0208a144(&self->child);
}
