/* func_0204ea00 @ 0x0204ea00, 0x3e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Pair {
    int a;
    int b;
};
extern int func_0204e97c(void *p, struct Pair *p1, struct Pair *p2);
extern int func_0204e6b8(void *addr);

int func_0204ea00(void *arg0, int *arg1)
{
    struct Pair p1, p2;
    int result = 0;

    p1.a = 0;
    p1.b = 0;
    p2.a = arg1[0];
    p2.b = arg1[1];

    if (func_0204e97c(arg0, &p1, &p2)) {
        result = func_0204e6b8((char *) arg0 + 0x24 + (p1.b << 11) + (p1.a << 9));
    }
    return result;
}
