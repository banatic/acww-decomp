/* func_ov004_0220c3a0 @ 0x0220c3a0, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov004_02256c00;
extern void func_0203efb0(int p, int flag);
extern void func_ov004_0220c144(int p, int flag);
extern void func_ov004_0220c318(int p);

int func_ov004_0220c3a0(int p)
{
    data_ov004_02256c00 = p;
    func_0203efb0(p, 0);
    func_ov004_0220c144(p, 0);
    func_ov004_0220c318(p);
    return 1;
}
