/* func_02065f88 @ 0x02065f88, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203d930(void *, void *, void *, int *);
extern void func_02065fc4(int, void *, void *, void *);
extern char data_021cd8c4[];
extern char data_021cd9b0[];
extern char data_021cd8ec[];

void func_02065f88(int a, int b, int c)
{
    struct {
        int x;
        int y;
        int z;
    } loc;
    loc.x = b;
    loc.y = c;
    func_0203d930(data_021cd8c4, data_021cd9b0, data_021cd8ec, &loc.z);
    loc.x = loc.z;
    func_02065fc4(a, data_021cd8c4, data_021cd9b0, data_021cd8ec);
}
