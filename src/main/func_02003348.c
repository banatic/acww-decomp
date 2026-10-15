/* func_02003348 @ 0x02003348, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021f42f4;
extern void func_02003378(int a, int b);
extern int func_0202f134(int a, int b, int c, int d);

int func_02003348(int p1, int p2, int p3, int p4, int p5)
{
    int local = p5;
    if (local == 0) {
        local = data_021f42f4;
    }
    func_02003378(p3, p4);
    return func_0202f134(p1, local, p2, 3);
}
