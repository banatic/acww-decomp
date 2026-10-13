/* func_0202d9dc @ 0x0202d9dc, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02015d60(void *a);
extern void *func_0202da08(void *a, int t);

void *func_0202d9dc(void *a)
{
    void *result = 0;
    int t = func_02015d60(a);
    void *p = func_0202da08(a, t);
    if (p) {
        result = *(void **) ((char *) p + 0x830);
    }
    return result;
}
