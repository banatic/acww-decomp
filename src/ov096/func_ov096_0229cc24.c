/* func_ov096_0229cc24 @ 0x0229cc24, 0x50 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov096_0229c2ec(void *, int);
extern void func_ov002_02208d30(void *, int);
extern void func_ov002_02208d4c(void *, int, int);
extern void func_ov096_0229d1d4(void *, int);

void func_ov096_0229cc24(unsigned int arg)
{
    func_ov096_0229c2ec((void *) arg, 0x40000);
    func_ov002_02208d30((void *) (arg + 0x294c), 0x22);
    func_ov002_02208d4c((void *) (arg + 0x294c), 0x1a, 0x22);
    func_ov002_02208d4c((void *) (arg + 0x294c), 0x15, 9);
    func_ov002_02208d4c((void *) (arg + 0x294c), 0x19, 0x22);
    func_ov096_0229d1d4((void *) arg, 0);
}
