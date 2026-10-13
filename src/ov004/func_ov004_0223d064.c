/* func_ov004_0223d064 @ 0x0223d064, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee470(int v);
extern void func_ov004_0223d2b0(int *a);
void func_ov004_0223d064(int *a)
{
    unsigned int i;
    for (i = 0; i < 2; i++) {
        if (a[i] != 0) {
            func_020ee470(a[i]);
        }
    }
    func_ov004_0223d2b0(a);
}
