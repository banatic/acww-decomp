/* func_0202d754 @ 0x0202d754, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02098e44(void *a, int b);
extern int func_02065ec0(void *p);

void *func_0202d754(void *arg)
{
    void *p;
    void *result;
    int i;

    p = func_02098e44(arg, 0);
    result = 0;
    i = (int) result;
    for (; i < 10; i++) {
        if ((unsigned char) (func_02065ec0(p) + 0xf9) <= 1) {
            result = p;
            break;
        }
        p = (char *) p + 0x100;
    }
    return result;
}
