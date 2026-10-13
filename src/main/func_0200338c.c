/* func_0200338c @ 0x0200338c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020ee7a4(void *a, void *b, int c);
extern char data_0213ff78[];

void *func_0200338c(void *a, void *b)
{
    void *result;
    void *arg1;
    int arg2;

    arg1 = a;
    if (b != 0) {
        arg2 = (int) b + 0x50;
        result = func_020ee7a4(data_0213ff78, arg1, arg2);
    } else {
        arg2 = 0;
        result = func_020ee7a4(data_0213ff78, arg1, arg2);
    }
    if (result != 0) {
        return *(void **) ((char *) result + 8);
    }
    return 0;
}
