/* func_0202f3e4 @ 0x0202f3e4, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202f660(void *a, void *b);
extern int func_0202f464(void *a, void *b);
extern int *func_0202f874(int *p, int arg);
extern void func_0202f8b4(void *a, void *b);

int func_0202f3e4(void *a0, void *a1, void *a2, int a3)
{
    int v1, v2, absv1;
    int pair[2];

    v1 = func_0202f660(a0, a1);
    v2 = func_0202f660(a0, a2);
    if (v2 >= 0) {
        absv1 = v1 < 0 ? -v1 : v1;
        if (absv1 <= a3) {
            if (func_0202f464(a0, a2) != 0 || func_0202f464(a0, a1) != 0) {
                char *p = (char *) a0 + 0x14;
                pair[0] = *(int *) p;
                pair[1] = *(int *) (p + 4);
                func_0202f874(pair, a3 - v1);
                func_0202f8b4(a1, pair);
                return 1;
            }
        } else {
            if (v1 < a3 + 0x200) {
                return 1;
            }
        }
    }
    return 0;
}
