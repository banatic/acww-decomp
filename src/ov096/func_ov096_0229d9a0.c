/* func_ov096_0229d9a0 @ 0x0229d9a0, 0x2a bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206fba8(unsigned char);
extern int func_ov096_0229c4dc(void *);
extern void func_0206fcb0(unsigned int argument0);
extern int func_ov096_022a18dc(void *, int);
extern void func_ov096_022a1540(void *);

void func_ov096_0229d9a0(void *arg0)
{
    func_0206fba8(*(unsigned char *) ((char *) arg0 + 0xb6));

    func_0206fcb0(func_ov096_0229c4dc(arg0));
    func_ov096_022a18dc(arg0, 8);
    func_ov096_022a1540(arg0);
}
