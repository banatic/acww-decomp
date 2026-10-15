/* func_ov003_02212768 @ 0x02212768, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_0221280c(void *p, void *q);
extern void *func_ov003_02212830(void *p, void *q, int size, void *b);

void func_ov003_02212768(char *a, void *b)
{
    int p[2];
    int q[2];

    p[0] = 0;
    p[1] = 0;
    func_ov003_0221280c(a + 0x8f0, p);
    q[0] = p[0];
    q[1] = p[1];
    func_ov003_02212830(a, q, 6, b);
}
