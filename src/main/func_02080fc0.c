/* func_02080fc0 @ 0x02080fc0, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021dc7bc[];
extern void *func_02098844(void *base, int index);
extern void func_02080ff8(int a, void *b, int c);

void func_02080fc0(int p0, int p1)
{
    void *g = data_021dc7bc;
    int i;
    if (g != 0) {
        for (i = 0; i < 4; i++) {
            void *r = func_02098844(g, i);
            if (r != 0) {
                func_02080ff8(p0, r, p1);
            }
        }
    }
}
