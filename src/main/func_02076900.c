/* func_02076900 @ 0x02076900, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02076900 UnkStruct_02076900;
extern void *data_020ccf94;
extern UnkStruct_02076900 data_021e5a2c;
extern void func_020736bc(void *g, signed char *dst, int n);
extern void func_020789f4(int *a, int *b, signed char *buf);
extern void *func_0207cec0(UnkStruct_02076900 *h, int a);
extern void *func_020807c0(void *x, int b);
extern void func_02081d18(void *x, int v);
void func_02076900(void)
{
    signed char buf[2];
    int ab[2];
    void *g = data_020ccf94;
    void *x;
    func_020736bc(g, &buf[0], 1);
    func_020789f4(&ab[0], &ab[1], buf);
    x = func_0207cec0(&data_021e5a2c, ab[0]);
    if (x != 0) {
        x = func_020807c0(x, ab[1]);
        if (x != 0) {
            func_020736bc(g, &buf[1], 1);
            func_02081d18(x, buf[1]);
        }
    }
}
