/* func_ov048_02260a60 @ 0x02260a60, 0x88 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02073144(void *);
extern void func_020a0194(void);
extern void *func_020984e8(void);
extern void *func_02099664(void *);
extern void *func_02077bcc(void *record);
extern long long func_020eb694(int);
extern void func_ov048_02262588(void *p, unsigned long long value);
extern int func_020a0174(void);
extern void *data_020ccf94;

int func_ov048_02260a60(void *obj)
{
    char *base;
    int n, i, ret;
    long long v;

    base = func_02073144(data_020ccf94);
    n = 0;
    for (i = 0; i < 0x20; i++) {
        if (*(unsigned char *) (base + i * 0x23 + 0x1a0) == 6) {
            n++;
        }
    }
    ret = 0;
    switch (*(unsigned char *) ((char *) obj + 0x813)) {
        case 0:
            func_020a0194();
            ret = 0x26;
            v = func_020eb694((int) func_02077bcc(func_02099664(func_020984e8())));
            func_ov048_02262588(obj, (unsigned long long) v);
            func_020a0174();
            break;
        case 1:
            if (n != 0) {
                ret = 0x6b;
            } else {
                ret = 0x46;
            }
            break;
        case 2:
            ret = 0x5d;
            break;
    }
    return ret;
}
