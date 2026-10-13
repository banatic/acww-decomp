/* func_0204da2c @ 0x0204da2c, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Pair {
    int a;
    int b;
};
void func_0204da2c(struct Pair *p)
{
    int i;
    for (i = 0; i < 4; i++) {
        p[i].a = 0;
        p[i].b = 0;
    }
}
