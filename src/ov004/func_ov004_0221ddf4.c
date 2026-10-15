/* func_ov004_0221ddf4 @ 0x0221ddf4, 0x108 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int w[8];
} T20;

extern int func_0208150c(int a);
extern int func_0200366c(int a, void *b, int c, void *d);
extern int func_ov004_0221df34(char *self);
extern int func_ov004_0221d4c0(void);
extern void func_ov004_0221df1c(char *self);
extern int func_020644cc(int n);
extern int func_020b66b0(void);
extern int func_0207cee4(void *a, int b);
extern int func_0207cec0(char *a, int b);
extern void *func_02094fd4(T20 *o);
extern void *func_02094fbc(T20 *o);
extern void func_02015e10(char *a, int b, int c);
extern int data_ov004_02257be0;
extern int data_ov004_02253928;
extern int data_021dc7a8;
extern int data_021e5a2c;

void func_ov004_0221ddf4(char *self, char *out)
{
    // DECLS
    T20 tmp;
    int k;
    int m;
    char *base;
    // ENDDECLS

    func_0200366c(func_0208150c(*(int *) (*(char **) (self + 0x1a4) + 0x830)), &data_ov004_02257be0, 0x28,
                  &data_ov004_02253928);
    *(int **) out = &data_ov004_02257be0;
    k = 2;
    if (func_ov004_0221df34(self) != 0) {
        k = 0;
    } else if (func_ov004_0221d4c0() != 0) {
        k = 1;
    }
    func_ov004_0221df1c(self);
    switch (k) {
        case 0:
            out[4] = (char) (func_020644cc(2) + 0x1a);
            break;
        case 1:
            out[4] = (char) (func_020644cc(4) + 0x1e);
            break;
        default:
            out[4] = (char) (func_020644cc(2) + 0x1c);
            break;
    }
    if (*(int *) (*(char **) (self + 0x1a4) + 0x8dc) != 0) {
        base = (char *) &data_021dc7a8;
        m = func_020b66b0();
        if (func_0207cee4(&data_021e5a2c, m) != 0) {
            func_02094fd4(&tmp);
            func_02015e10(*(char **) (self + 0x1a4) + 0x89c, func_0208150c(func_0207cec0(base + 0x9284, m)), 1);
            func_02094fbc(&tmp);
        }
        if (*(char **) (self + 0x1a4) != 0 && *(int *) (*(char **) (self + 0x1a4) + 0x830) != 0) {
            func_02015e10(*(char **) (self + 0x1a4) + 0x89c, func_0208150c(*(int *) (*(char **) (self + 0x1a4) + 0x830)), 0);
        }
    }
}
