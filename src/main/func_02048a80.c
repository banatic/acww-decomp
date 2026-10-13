/* func_02048a80 @ 0x02048a80, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02048b54(void);
extern void func_02048b0c(int a, int b, int c, int d);
extern void func_02048ab0(int a, int b, int c, int d);

void func_02048a80(int a, int b, int c, int d)
{
    func_02048b54();
    func_02048b0c(a, b, c, d);
    func_02048ab0(a, b, c, d);
}
