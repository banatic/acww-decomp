/* func_020930a0 @ 0x020930a0, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021d5658;
extern void *data_020e27c8;
extern void *data_020e2904[3];
extern void func_02091494(void *, int, int, int, int, int, int);
extern int func_02090c2c(int, int, int, void *);

int func_020930a0(int a0, int a1, int a2, int a3, int a4)
{
    int i;
    void **p;
    func_02091494(&data_021d5658, -1, a0, a1, a2, a3, -1);
    if (func_02090c2c(a4, a1, a2, &data_020e27c8) == 0) {
        goto ret3;
    }
    i = 0;
    p = data_020e2904;
    for (; i < 3; i++) {
        if (func_02090c2c(0x54, a1, a2, &p[i]) == 0) {
            return 3;
        }
    }
    return 1;
ret3:
    return 3;
}
