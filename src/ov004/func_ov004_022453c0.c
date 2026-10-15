/* func_ov004_022453c0 @ 0x022453c0, 0x94 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct Elem {
    char pad_00[0x1c];
} Elem;

typedef struct Row {
    unsigned char id;
    char pad_01[3];
    Elem *arr;
    unsigned int n;
} Row;

extern Row data_ov004_0224b868[];
extern int func_020b65c4(void);
extern int func_ov004_02245544(Elem *e);
extern unsigned int *func_ov004_02245554(Elem *e);
extern int func_ov004_0224554c(Elem *e);
extern int func_ov004_02245548(Elem *e);
extern short func_ov004_0224553c(Elem *e);
extern int func_ov004_02245538(Elem *e);
extern int func_ov004_02245534(Elem *e);
extern void func_ov004_0221b224(int a, void *position, int c, int d, short e, int f, int g);

void func_ov004_022453c0(void)
{
    // DECLS
    unsigned int j;
    Elem *e;
    Row *r;
    unsigned int n;
    unsigned int i;
    int k;
    // ENDDECLS

    k = func_020b65c4();
    for (i = 0; i < 7; i++) {
        r = &data_ov004_0224b868[i];
        if (k == data_ov004_0224b868[i].id) {
            for (j = 0, n = r->n; j < n; j++) {
                e = &r->arr[j];
                func_ov004_0221b224(func_ov004_02245544(e), func_ov004_02245554(e), func_ov004_0224554c(e),
                                    func_ov004_02245548(e), func_ov004_0224553c(e), func_ov004_02245538(e),
                                    func_ov004_02245534(e));
            }
            break;
        }
    }
}
