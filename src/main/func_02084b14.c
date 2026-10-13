/* func_02084b14 @ 0x02084b14, 0x3e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(void *);
extern int func_02085d2c(void *, void *);

int func_02084b14(void *p, int n)
{
    int i;
    void *sp;
    int arr[2];
    int *q;

    arr[0] = 0;
    arr[1] = 0;
    sp = arr;
    func_0209e474(sp);
    i = 0;
    q = arr;
    while (i < n) {
        if (func_02085d2c(*(void **) p, q) != 0) {
            return i;
        }
        p = (char *) p + 8;
        i++;
    }
    return -1;
}
