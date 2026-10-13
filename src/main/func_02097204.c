/* func_02097204 @ 0x02097204, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020984e8(void);
extern void *func_02098a0c(void);
extern void func_02097cf8(void *, char *);

void func_02097204(char *a, int b)
{
    int i;
    void *p;
    func_020984e8();
    p = func_02098a0c();
    for (i = 0; i < b; i++) {
        func_02097cf8(p, a);
        a++;
    }
}
