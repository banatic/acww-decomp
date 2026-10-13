/* func_02079924 @ 0x02079924, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern int data_021e5a2c;
extern void *func_0207cec0(int *ctx, int key);
extern int func_0208150c(void *p);
extern int func_02003704(int val);
extern int func_02079b7c(int a, int b, int c);
extern int func_02079994(int a, void *p1, void *p2);

int func_02079924(int a, int b, int c)
{
    int *base = &data_021e5a2c;
    void *p1 = func_0207cec0(base, b);
    void *p2 = func_0207cec0(base, c);
    int result = 0;

    if (p1 != 0 && func_02003704(func_0208150c(p1)) != 0 && p2 != 0 && func_02003704(func_0208150c(p2)) != 0) {
        int x = func_02079b7c(a, b, c);
        int y = func_02079994(a, p1, p2);
        result = y + ((5 * x) >> 1);
    }
    return result;
}
