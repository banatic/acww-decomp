/* func_ov123_0229c044 @ 0x0229c044, 0x38 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200284c(int, int, int);

void func_ov123_0229c044(void *arg)
{
    int *p;
    p = (int *) ((char *) arg + 0x98);
    func_0200284c(6, 0, -*p);
    func_0200284c(4, 0, -*p);
    func_0200284c(3, 0, -*p);
}
