/* func_ov004_0221e1e0 @ 0x0221e1e0, 0xe0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f818(int *out0, int *out1, const int *in);
extern int func_02031a08(int i, int j);
extern int func_020644cc(int n);
extern void func_0204f794(int *out, int i, int j);
extern int func_020e8ed8(int dx, int dy);
extern int func_020e8b4c(int a, int b);

int func_ov004_0221e1e0(int *out, int *in, int a)
{
    // DECLS
    int ang;
    int count;
    int gx;
    int j;
    int i;
    int gz;
    int target;
    int k;
    // ENDDECLS

    func_0204f818(&gx, &gz, in);
    count = 0;
    for (j = 0; j < 0xe; j++) {
        for (i = 0; i < 0x10; i++) {
            if (i != gx && j != gz && func_02031a08(i, j) != 0) {
                count++;
            }
        }
    }
    out[0] = in[0];
    out[1] = in[1];
    out[2] = in[2];
    if (count != 0) {
        target = func_020644cc(count);
        k = 0;
        for (j = 0; j < 0xe; j++) {
            for (i = 0; i < 0x10; i++) {
                if (i != gx && j != gz && func_02031a08(i, j) != 0) {
                    if (k == target) {
                        func_0204f794(out, i, j);
                        ang = func_020e8ed8(out[0] - in[0], out[2] - in[2]);
                        if (func_020e8b4c(a, ang) < 0x2000) {
                            ang = a;
                        }
                        return ang;
                    }
                    k = k + 1;
                }
            }
        }
    }
    return a;
}
