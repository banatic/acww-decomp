/* func_0201c2c8 @ 0x0201c2c8, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096614(unsigned char *, unsigned int *, unsigned int *, int, void *);
extern void *func_0200322c(void *, unsigned int *);
extern void *func_02096190(void *);
extern void *func_0201c314(void *, void *);

void *func_0201c2c8(void *arg0, void *arg1)
{
    void *result = 0;
    unsigned char flag = 0;
    unsigned int dataA[2];
    unsigned int dataB[2];

    if (func_02096614(&flag, dataA, dataB, -1, arg1)) {
        arg0 = (unsigned char *) arg0 + 0x5c;
        result = func_0200322c(arg0, dataA);
    } else {
        void *p;

        p = func_02096190(arg1);
        if (p != 0) {
            result = func_0201c314(arg0, p);
        }
    }

    return result;
}
