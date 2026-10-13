/* func_0209b3cc @ 0x0209b3cc, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02063ccc(void *, int, int);
extern void func_020638d4(void *, void *, int, int, int, int, int);
extern void func_02063cc8(void *);
extern int func_0209bb68(void *, void *);

int func_0209b3cc(void *param)
{
    int d;
    struct {
        int x;
        int y;
    } e;

    func_02063ccc(&e, 2, 0);
    func_020638d4(&d, &e, 0, 0, 1, 1, 0);
    func_02063cc8(&e);
    func_0209bb68(param, &d);

    return 1;
}
