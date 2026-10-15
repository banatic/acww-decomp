/* func_020a0af8 @ 0x020a0af8, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Vec3 {
    int v[3];
} Vec3;

extern Vec3 data_020e3a74;
extern Vec3 data_020e3a80;
extern int *data_020ccf94;

extern int func_02073dd4(int *p, int n);
extern int func_020a2450(int p, int n);
extern int func_02090040(int);
extern int func_02090158(void);
extern int func_02075e00(int, int, int, int, int, int);

int func_020a0af8(int param)
{
    Vec3 a = data_020e3a74;
    Vec3 b = data_020e3a80;
    int i = 2;
    int val = 2;
    int *g = data_020ccf94;

    do {
        int j = i + 1;
        if (func_02073dd4(g, j) != 0) {
            int res = func_020a2450(param, j);
            if (res < 4) {
                func_02090040(res);
                if (func_02090158() != 0) {
                    a.v[i] = val;
                    b.v[i] = res;
                } else {
                    a.v[i] = 1;
                }
            } else {
                a.v[i] = 0;
            }
        }
        i--;
    } while (i >= 0);

    return func_02075e00(a.v[0], b.v[0], a.v[1], b.v[1], a.v[2], b.v[2]);
}
