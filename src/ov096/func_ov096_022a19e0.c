/* func_ov096_022a19e0 @ 0x022a19e0, 0x2a bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_022a192c(void *);
extern int func_ov096_022a142c(void *);
extern int func_ov096_022a1a0c(void *);
extern int func_ov096_022a1424(void *);

int func_ov096_022a19e0(void *p)
{
    if (func_ov096_022a192c(p)) {
        return 1;
    }
    func_ov096_022a142c(p);
    func_ov096_022a1a0c(p);
    func_ov096_022a1424(p);
    return 1;
}
