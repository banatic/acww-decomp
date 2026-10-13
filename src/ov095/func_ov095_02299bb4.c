/* func_ov095_02299bb4 @ 0x02299bb4, 0x5e bytes, Thumb, module ov095
 * mwccarm 1.2/base -O1,s
 */

extern int func_ov095_02299f3c(void *, void *);
extern int func_ov095_02299e80(void *, void *);
extern int func_ov095_02299cf8(void *, void *);
extern int func_ov095_02299c14(void *, void *);

int func_ov095_02299bb4(void *p0, void *p1)
{
    int result;

    if (func_ov095_02299f3c(p0, p1) != 0) {
        return 1;
    }
    result = 0;
    switch (*(unsigned char *) ((char *) p0 + 0x42)) {
        case 0:
            return func_ov095_02299e80(p0, p1);
        case 1:
        case 2:
            return func_ov095_02299cf8(p0, p1);
        case 3:
            break;
        case 4:
        case 5:
            return func_ov095_02299c14(p0, p1);
    }
    return result;
}
