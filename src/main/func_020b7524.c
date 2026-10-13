/* func_020b7524 @ 0x020b7524, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b7338(int a, unsigned char b);
extern int func_020b755c(int a, int *b, int *c, unsigned char *d);

int func_020b7524(int a, int *p1, unsigned char *p2)
{
    unsigned char byte_tmp;
    int word_tmp;
    int arr_tmp[3];

    if (p1 == 0) {
        p1 = &word_tmp;
    }
    if (p2 == 0) {
        p2 = &byte_tmp;
    }
    if (func_020b755c(a, arr_tmp, p1, p2)) {
        return func_020b7338(*p1, *p2);
    }
    return 0;
}
