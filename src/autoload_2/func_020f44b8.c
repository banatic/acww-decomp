/* func_020f44b8 @ 0x020f44b8, 0x40 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fd1bc[];
extern void func_020f6700(int);
extern void func_020f43f8(void *, int);

int func_020f44b8(void *arg)
{
    int val;
    val = *(int *) (data_021fd1bc + 0x30);
    func_020f6700(val);
    data_021fd1bc[0x4d] = 1;
    func_020f43f8(arg, 15);
    ((char *) arg)[5] = 1;
    return 1;
}
