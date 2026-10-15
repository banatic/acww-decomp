/* func_02024194 @ 0x02024194, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct TwoWords {
    unsigned int a;
    unsigned int b;
} data_020d9338;
extern unsigned int data_020d9d24[];

extern int func_0202d9c4(void *self);
extern int func_0209bcc4(int prev, int *out_idx);
extern int func_0208150c(unsigned int val);
extern int func_020036e8(int a);
extern int func_0202da38(void *a, void *b, void *c, int d, int e, int offset, int scale, int h, int i);

void func_02024194(void *self, void *out)
{
    struct {
        unsigned int a;
        unsigned int b;
        int c;
    } cond;
    int idx;
    int res, result;
    void *ptr100;
    unsigned int val830;

    *(struct TwoWords *) &cond = data_020d9338;
    cond.c = 0;

    result = func_0202d9c4(self);
    func_0209bcc4(result, &cond.c);

    idx = cond.c;
    if (idx < 5) {
        cond.a = data_020d9d24[idx];
    }

    if (cond.a == 0) {
        return;
    }

    ptr100 = *(void **) ((char *) self + 0x100);
    val830 = *(unsigned int *) ((char *) ptr100 + 0x830);
    res = func_0208150c(val830);
    result = func_020036e8(res);

    func_0202da38(self, (char *) self + 0x104, (char *) self + 0x122, 0x1e, result, cond.a, *((unsigned char *) &cond.b), 0,
                  0);

    *(void **) out = (char *) self + 0x104;
    *((unsigned char *) out + 4) = *((unsigned char *) self + 0x122);
}