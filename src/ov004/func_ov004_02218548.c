/* func_ov004_02218548 @ 0x02218548, 0x68 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b;
} UnkStruct_02218548;
typedef struct {
    char *p;
    unsigned int n;
} Tbl;

extern Tbl data_ov004_022476b0[];
extern unsigned int data_ov004_022476b4[];
extern void func_ov004_0220ff74(char *self, int *x, char *y);
extern UnkStruct_02218548 *func_ov004_02218394(UnkStruct_02218548 *p, unsigned int i);
extern void func_0204f818(int *out0, int *out1, const int *in);

unsigned int func_ov004_02218548(char *self, UnkStruct_02218548 *arg)
{
    // DECLS
    int loc[3];
    unsigned int i;
    char *base;
    UnkStruct_02218548 *e;
    // ENDDECLS

    base = data_ov004_022476b0[*(unsigned int *) (self + 0x784)].p;
    if (base != 0) {
        for (i = 0; i < data_ov004_022476b0[*(unsigned int *) (self + 0x784)].n; i++) {
            func_ov004_0220ff74(self, loc, base + i * 0xc);
            e = func_ov004_02218394(arg, i);
            func_0204f818(&e->a, &e->b, loc);
        }
        return *(unsigned int *) ((char *) data_ov004_022476b4 + *(unsigned int *) (self + 0x784) * 8);
    }
    return 0;
}
