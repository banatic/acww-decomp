/* func_ov003_02223a04 @ 0x02223a04, 0x8c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_0222378c(void *, int *);
extern void func_ov003_02223274(void *);

void func_ov003_02223a04(void *p)
{
    int i, j, off;
    char *base;
    int *q;

    for (i = 0; i < 5; i++) {
        q = (int *) ((char *) p + i * 0x18 + 0x1dd4);
        if (*q != 0) {
            func_ov003_0222378c(p, q);
        }
    }

    for (i = 0; i < 3; i++) {
        j = 0;
        base = (char *) p + i * 0x530;
        do {
            func_ov003_02223274(base + j * 0x14c);
            j++;
        } while (j < 4);
    }

    for (i = 0; i < 4; i++) {
        off = i * 0x14c;
        func_ov003_02223274((char *) p + 0xf90 + off);
        func_ov003_02223274((char *) p + 0x18a4 + off);
    }
}
