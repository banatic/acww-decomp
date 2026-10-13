/* func_0205ac5c @ 0x0205ac5c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205bd80(void *);
extern int func_0205bd88(void *);
extern int func_0205bd84(void *);

int func_0205ac5c(int a, void *b)
{
    int v1;
    int v2;
    v1 = func_0205bd80(b);
    v2 = func_0205bd88(b);
    return 100 * (v1 + (v2 + func_0205bd84(b)));
}
