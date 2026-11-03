/* room_object_02253058_9: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02218608 @ 0x02218608, 0x4 bytes, Thumb
 * func_ov004_02218604 @ 0x02218604, 0x4 bytes, Thumb
 * func_ov004_022185b0 @ 0x022185b0, 0x54 bytes, Thumb
 * func_ov004_02218548 @ 0x02218548, 0x68 bytes, Thumb
 */

typedef struct {
    int a, b;
} UnkStruct_02218548;

typedef struct {
    char *p;
    unsigned int n;
} Tbl;

extern void func_ov004_0220ff74(void *self, int *t, char *p);
extern char *func_ov004_02218394(void *a, unsigned i);
extern void func_0204f818(char *a, char *b, int *t);
extern char *data_ov004_02250668[];
extern Tbl data_ov004_022476b0[];
extern unsigned int data_ov004_022476b4[];

int func_ov004_02218608(void)
{
    return 1;
}

int func_ov004_02218604(void)
{
    return 1;
}

int func_ov004_022185b0(char *self, void *a)
{
    char *p = data_ov004_02250668[*(int *) (self + 0x784)];
    unsigned i;
    int t[3];
    char *q;

    if (p != 0) {
        for (i = 0; i < 2; i++) {
            func_ov004_0220ff74(self, t, p + 0xc * i);
            q = func_ov004_02218394(a, i);
            func_0204f818(q, q + 4, t);
        }
        return 2;
    }
    return 0;
}

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
            func_ov004_0220ff74((void *) self, loc, base + i * 0xc);
            e = (UnkStruct_02218548 *) func_ov004_02218394((void *) arg, i);
            func_0204f818((char *) (&e->a), (char *) (&e->b), (int *) loc);
        }
        return *(unsigned int *) ((char *) data_ov004_022476b4 + *(unsigned int *) (self + 0x784) * 8);
    }
    return 0;
}
