/* func_020b7e04 @ 0x020b7e04, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b7d24(void *, void *);

int func_020b7e04(void *a, char *b)
{
    unsigned int i;
    int flag = 1;
    int one = 1;
    int zero = 0;
    int result;

    for (i = 0; i < 10; i++) {
        result = func_020b7d24(a, b);
        b += 0x44;
        flag = (flag | result) ? one : zero;
    }
    return flag;
}
