/* func_ov111_022a0910 @ 0x022a0910, 0x30 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov095_0229b280(void *);
extern void func_ov111_022a0970(void *);
extern void func_ov002_02208090(void *, int);
extern int func_ov111_0229efd8(void *, int);
extern void func_ov111_022a08bc(void *);

void func_ov111_022a0910(void *param)
{
    func_ov095_0229b280((char *) param + 0xac);
    func_ov111_022a0970(param);
    func_ov002_02208090(param, 2);
    if (func_ov111_0229efd8(param, 0x20) == 0) {
        func_ov111_022a08bc(param);
    }
}
