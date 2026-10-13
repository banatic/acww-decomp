/* func_0208e9e0 @ 0x0208e9e0, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208a1b0(void *ptr, int arg);
extern int func_0208a198(void *ptr, int arg);

typedef struct {
    char pad_00[0x14];
    int unk_14;
    char pad_18[0x24];
    int unk_3C;
} UnkStruct_0208e9e0;

void func_0208e9e0(UnkStruct_0208e9e0 *self, int *out1, int *out2)
{
    int r4 = 0;
    int r1 = r4;
    int *p;
    int t1, t2, t3, t4;

    if (self->unk_3C == 2) {
        t1 = func_0208a1b0(&self->unk_14, -1);
        t2 = func_0208a1b0(&self->unk_14, 0);
        r4 = t1 - t2;
        t3 = func_0208a198(&self->unk_14, -1);
        p = &self->unk_14;
        t4 = func_0208a198(p, 0);
        r1 = t3 - t4;
    } else if (self->unk_3C == 3) {
        t1 = func_0208a1b0(&self->unk_14, 0);
        t2 = func_0208a1b0(&self->unk_14, -1);
        r4 = t1 - t2;
        t3 = func_0208a198(&self->unk_14, 0);
        p = &self->unk_14;
        t4 = func_0208a198(p, -1);
        r1 = t3 - t4;
    }

    *out1 = r4;
    *out2 = r1;
}
