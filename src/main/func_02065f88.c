/* func_02065f88 @ 0x02065f88, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203d930(void *, void *, void *, int *, const unsigned char *, int);
extern void func_02065fc4(int, void *, void *, void *, int);
extern char data_021cd8c4[];
extern char data_021cd9b0[];
extern char data_021cd8ec[];

void func_02065f88(int a, int b, int c)
{
    int result;
    func_0203d930(data_021cd8c4, data_021cd9b0, data_021cd8ec, &result, (const unsigned char *) b, c);
    func_02065fc4(a, data_021cd8c4, data_021cd9b0, data_021cd8ec, result);
}
