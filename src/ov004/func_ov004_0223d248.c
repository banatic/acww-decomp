/* func_ov004_0223d248 @ 0x0223d248, 0x64 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021fbe94;
extern void *func_020e9948(void *h, int sz);
extern void *func_020ba294(void *object);
extern void *func_0203cbcc(void *object);

void func_ov004_0223d248(void *self)
{
    void *h = data_021fbe94;
    unsigned int i;
    void **p;
    void *x;

    for (i = 0; i < 2; i++) {
        p = (void **) ((char *) self + i * 4);
        if (p[5] == 0) {
            p[5] = func_020e9948(h, 0x10c4);
            x = p[5];
            if (x != 0) {
                x = func_020ba294(x);
            }
            p[5] = x;
        }
        if (p[7] == 0) {
            p[7] = func_020e9948(h, 0x20c4);
            x = p[7];
            if (x != 0) {
                x = func_0203cbcc(x);
            }
            p[7] = x;
        }
    }
}
