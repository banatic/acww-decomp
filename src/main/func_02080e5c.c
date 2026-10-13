/* func_02080e5c @ 0x02080e5c, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021dc7bc;
extern int func_02098844(int a, int b);
extern void func_02099870(void);
extern int func_020951bc(void);
extern void func_02080ea4(int a, int b, int c);

void func_02080e5c(int p1, int p2)
{
    if ((int) &data_021dc7bc) {
        int i;
        for (i = 0; i < 4; i++) {
            int r = func_02098844((int) &data_021dc7bc, i);
            if (r != 0) {
                func_02099870();
                if (func_020951bc() != 0) {
                    func_02080ea4(p1, r, p2);
                }
            }
        }
    }
}
