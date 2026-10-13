/* func_ov003_0222625c @ 0x0222625c, 0x64 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_02236cf4[];
extern void *data_ov003_0223a218[];
extern void *data_ov003_0223cf74;
extern int func_0204cab4(void *self);
extern int func_020555a4(void *rec, void *g1, void *g2, int k, void *y, int *ip, int q);

int func_ov003_0222625c(char *self, void *b)
{
    int i;
    int *t;
    int r = func_0204cab4(self);
    i = 0;
    t = &data_ov003_02236cf4[r];
    while (i < 5) {
        if (func_020555a4(self + 0x43e8 + i * 0x9c, data_ov003_0223a218[i], data_ov003_0223cf74, 0, b, t, 1) == 0) {
            return 0;
        }
        i++;
    }
    return 1;
}
