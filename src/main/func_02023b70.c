/* func_02023b70 @ 0x02023b70, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int n;
    unsigned char b;
} UnkStruct_02023b70;
typedef void (*Fn)(void *self, UnkStruct_02023b70 *out);

typedef struct {
    int fn;
    int adj;
} Pmf;

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    Pmf pmf;
} UnkStruct_02023b70_2;

extern int data_021c2f74;
extern int data_021c2fa4;
extern int func_02099fe8(UnkStruct_02023b70_2 *self);
extern void func_0202da88(UnkStruct_02023b70_2 *self, void *tbl);
extern void func_0206844c(int a, void *b, int c);

void func_02023b70(UnkStruct_02023b70_2 *self)
{
    unsigned char arg;
    UnkStruct_02023b70 out;
    Fn f;

    if (func_02099fe8(self) != -1) {
        func_0202da88(self, &data_021c2f74);
    } else {
        func_0202da88(self, &data_021c2fa4);
    }
    if (((volatile Pmf *) &self->pmf)->fn != 0) {
        volatile Pmf *pm;
        int adj;
        char *t;

        pm = (volatile Pmf *) &self->pmf;
        adj = pm->adj;
        t = (char *) self + (adj >> 1);
        if (adj & 1) {
            f = (Fn) * (int *) (*(char **) t + pm->fn);
        } else {
            f = (Fn) pm->fn;
        }
        f(t, &out);
    }
    arg = out.b;
    func_0206844c(self->unk_40, &arg, out.n);
}
