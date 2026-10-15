/* func_02097234 @ 0x02097234, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern void *func_02098a0c(int);
extern int func_02097cd4(void *x, char *p);

char *func_02097234(char *p1, int p2, int p3)
{
    int cnt;
    char *p;
    int i;
    void *x;

    x = func_02098a0c((int) func_020984e8());

    cnt = 0;
    p = p1;
    i = cnt;
    while (i < p2) {
        if (func_02097cd4(x, p) == 0) {
            if (cnt == p3) {
                return p;
            }
            cnt++;
        }
        p++;
        i++;
    }
    return p1;
}
