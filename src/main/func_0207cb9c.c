/* func_0207cb9c @ 0x0207cb9c, 0xb8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207cf14(void *p, int x);
extern int func_0207cf74(unsigned int index);
extern int func_0207b3dc(void *p);
extern int func_0208150c(void *p);
extern int func_02003704(int t);
extern int func_0207f074(void *p);
extern int func_0207cc54(int a, int b, int c);
extern int func_0207cec0(void *p, int x);

int func_0207cb9c(void *p, int *arr, int count)
{
    int i;
    unsigned char mask;
    int v;
    int b;
    unsigned char result;
    int count2;
    char *cur;
    int t;

    mask = 0;
    i = 0;
    while (i < count) {
        if (*arr != 0) {
            v = func_0207cf14(p, *arr);
            if (func_0207cf74((unsigned int) v) != 0) {
                mask = (unsigned char) (mask | (1 << v));
            }
        }
        arr++;
        i++;
    }

    b = func_0207b3dc(p);
    if (func_0207cf74((unsigned int) b) != 0) {
        mask = (unsigned char) (mask | (1 << b));
    }

    cur = p;
    result = 0;
    count2 = 0;
    i = count2;
    do {
        t = func_0208150c(cur);
        if (((mask >> i) & 1) == 0) {
            if (func_02003704(t) != 0 && func_0207f074(cur) != 0) {
                result = (unsigned char) (result | (1 << i));
                count2++;
            }
        }
        cur += 0x7ec;
        i++;
    } while (i < 8);

    return func_0207cec0(p, func_0207cc54(result, count2, 8));
}