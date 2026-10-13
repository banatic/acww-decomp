/* func_ov004_022309f8 @ 0x022309f8, 0x128 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02055050(void *);
extern void func_02055060(void *, int, int, int, int, int);
extern int func_02055140(void *, int);
extern int func_02055e00(void *);
extern void func_020563dc(void *, int);
extern void func_02056478(void *, int, int, int, int);
extern int func_0205650c(void *, int, int);
extern int func_ov004_0222c3a4(void *, int);
extern int func_ov004_0222c3c4(void *, int);
extern void func_ov004_0222c600(void *, void *, void *);
extern void func_ov004_02230438(void *, int, void *, void *);
extern void func_ov004_0223080c(void *, int);
extern void *data_021c9b24;
extern void *data_ov004_022556dc;
extern void *data_ov004_022556f4;
extern void *data_ov004_02255710;
extern void *data_ov004_02255728;
extern void *data_ov004_02255744;
extern void *data_ov004_0225575c;
extern void *data_ov004_02255778;
extern void *data_ov004_02255790;
extern void *data_ov004_02258870;

int func_ov004_022309f8(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) ((char *) &data_ov004_02258870) = self;
    func_ov004_0222c600(self, &data_ov004_022556dc, &data_ov004_022556f4);
    func_ov004_02230438(self, 0x0, &data_ov004_02255710, &data_ov004_02255728);
    func_ov004_02230438(self, 0x1, &data_ov004_02255744, &data_ov004_0225575c);
    func_ov004_02230438(self, 0x2, &data_ov004_02255778, &data_ov004_02255790);
    if (func_ov004_0222c3c4(self + 0x600, 0x0) != 0x0 &&
        func_02055140(self + 0x400, *(int *) ((char *) &data_021c9b24)) != 0x0) {
        func_02055060(self + 0x400, func_ov004_0222c3c4(self + 0x600, 0x0), 0x1, 0x1000, 0x0, 0x0);
        func_02055050(self + 0x400);
        *(void **) (self + 0x4ac) = 0x0;
    }
    if (func_0205650c(self + 0x6b4, *(int *) (self + 0x3a4), *(int *) ((char *) &data_021c9b24)) != 0x0) {
        func_02056478(self + 0x6b4, func_ov004_0222c3a4(self + 0x55c, 0x0), 0x1, 0x1000, 0x0);
        func_020563dc(self + 0x6b4, func_02055e00(self + 0x348));
        *(void **) (self + 0x6c4) = 0x0;
    }
    func_ov004_0223080c(self, 0x0);
    return 0x1;
}
