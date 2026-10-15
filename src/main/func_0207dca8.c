/* func_0207dca8 @ 0x0207dca8, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021dc7bc[];
extern void *func_02098844(void *base, int i);
extern int func_02099870(int);
extern int func_020951bc(void *);
extern void *func_02099640(void *a);
extern int func_0207ef54(void *arg, void *b);

int func_0207dca8(void *arg)
{
    void *base = data_021dc7bc;
    int i;
    for (i = 0; i < 4; i++) {
        void *a = func_02098844(base, i);
        if (func_020951bc((void *) func_02099870((int) a)) != 0) {
            void *b = func_02099640(a);
            if (func_0207ef54(arg, b) != 0) {
                return 0;
            }
        }
    }
    return 1;
}
