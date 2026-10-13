/* func_020ad7f4 @ 0x020ad7f4, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern void func_020adb70(int, int, int, int, int, int, int);
extern void func_020ad8d0(int, int, int, int);
extern int func_020b6744(int);
extern void func_02073820(void *);
extern void func_02073770(void *, int, int);
extern void *data_020ccf94;

void func_020ad7f4(unsigned int *p, int idx)
{
    unsigned int word, t1, t2, t3;
    unsigned int a, b;
    int flag;
    void *q;

    word = *p;
    t1 = word << 26;
    a = t1 >> 26;
    t2 = word >> 26;
    t3 = t2 << 24;
    b = t3 >> 24;
    flag = ((word << 6) >> 31) ? 1 : 0;

    if (b == 10) {
        func_020adb70(a, 0, b, 1, 1, 0, 1);
    } else if (b == 15) {
        func_020ad8d0(a, b, 0, 1);
    } else {
        if (func_020b6744(b) != 0) {
            func_020adb70(a, ((*p << 7) >> 13), b, flag, 0, 0, 1);
        }
    }

    if (a != 0x3F) {
        q = data_020ccf94;
        func_02073820(q);
        func_02073770(q, 0x27, idx);
    }
}
