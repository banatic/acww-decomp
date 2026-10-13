/* func_02029910 @ 0x02029910, 0x108 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void *p);
extern void *func_02099734(void *p);
extern unsigned short *func_02098f48(void *p, int a);
extern int func_0209b878(void *p, unsigned char a);
extern int func_0209b8bc(void *p);
extern void func_0209b750(void *p, int a, unsigned char b);
extern int func_02098e8c(void *p, int a);
extern int func_0204bcdc(unsigned short *p);
extern int func_0204bc64(unsigned short *p);

static __inline int sameId(unsigned short *p, unsigned short *q)
{
    int v;
    v = func_0204bc64(p);
    if (v == func_0204bc64(q)) {
        return 1;
    }
    return 0;
}

static __inline int sameRaw(unsigned short *p, unsigned short *q)
{
    if (*p == *q) {
        return 1;
    }
    return 0;
}

unsigned short func_02029910(void *param)
{
    void *data;
    unsigned short *ptr;
    unsigned short arr[4];
    int flag1;
    unsigned short *ptr2;
    int flag2;
    unsigned short result;
    int i;
    int j;

    data = func_02099734(func_020984e8(param));
    ptr = func_02098f48(data, 0);
    arr[1] = 0xfff1;
    arr[2] = 0xfff1;
    arr[3] = 0xfff1;
    ptr2 = &arr[1];
    result = 0;

    for (i = 0; i < 3; i++) {
        if (func_0209b878(param, (unsigned char) i) == 0) {
            func_0209b750(arr, func_0209b8bc(param), (unsigned char) i);
            *(ptr2 + i) = arr[0];
        } else {
            *(ptr2 + i) = 0xfff1;
        }
    }

    flag1 = 0;
    flag2 = 0;

    for (i = 0; i < 15; ptr++, i++) {
        int ok;
        int found;
        if (func_02098e8c(data, i) != 0) {
            continue;
        }
        ok = flag1;
        if (((*ptr) >= 0x450c) && ((*ptr) <= 0x45db)) {
            ok = 1;
        }
        if (ok == 0) {
            continue;
        }
        for (j = flag2; j < 3; j++) {
            if (func_0204bcdc(ptr) != 0) {
                found = sameId(ptr, ptr2 + j);
            } else {
                found = sameRaw(ptr, ptr2 + j);
            }
            if (found) {
                result = (unsigned short) (result | (1 << i));
                break;
            }
        }
    }

    return result;
}
