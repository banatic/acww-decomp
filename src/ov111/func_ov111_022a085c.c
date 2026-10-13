/* func_ov111_022a085c @ 0x022a085c, 0x2e bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207f04(int, int, int, int, int);
extern void func_ov002_02207e80(int, int, int, int);

void func_ov111_022a085c(int arg0)
{
    int local_0;
    int local_1;

    local_0 = 0x30;
    func_ov002_02207f04(arg0, 8, 0, 0, local_0);
    func_ov002_02207e80(arg0, 6, 0, 0);
    *(unsigned char *) (arg0 + 0x8c) = 5;
}
