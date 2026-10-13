/* func_0203394c @ 0x0203394c, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020da1a4;
extern int data_020da210;
extern void func_0202f8fc(void *ptr, int x, int y);
extern void func_020342a4(void *ptr);
extern void func_020338c4(int *a, int b, int c, int d, int e, int f, int g, int h);

int *func_0203394c(int *a, int b, int c, int d, int e, int f, int g, int h)
{
    *a = (int) &data_020da1a4;
    func_0202f8fc((char *) a + 4, 0, 0);
    func_0202f8fc((char *) a + 0xc, 0, 0);
    func_0202f8fc((char *) a + 0x14, 0, 0);
    func_020342a4((char *) a + 0x20);
    *a = (int) &data_020da210;
    func_020338c4(a, b, c, d, e, f, g, h);
    return a;
}
