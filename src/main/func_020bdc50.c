/* func_020bdc50 @ 0x020bdc50, 0xc0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020bdd10(char *work, int a, int b, int *c);
extern int func_020be1c4(char *work, int a);
extern int func_020be0f8(char *work, int a, int b);
extern void func_020bee74(char *a, int b, char *c);
extern void func_020be160(char *a, int b);
extern void func_020bf948(char *a);
extern void func_020bf810(char *a, int b);
extern signed char data_020d2bb9[];

void *func_020bdc50(char *work, int param1, int param2, int *param3, int param4)
{
    int result1, result2, index;
    char *p;

    result1 = func_020bdd10(work, param1, param4, param3);
    p = 0;
    result2 = func_020be1c4(work, result1);
    if (result2 == 5) {
        goto done;
    }
    index = func_020be0f8(work, param1, param2);
    if (index == 0x3c) {
        goto done;
    }
    if (result2 != 6) {
        func_020bee74(work + 0x1b30 + result2 * 12, result1, work + 0x2eb8);
        func_020be160(work, result2);
    }
    index *= 0x74;
    p = work + index;
    func_020bf948(p);
    *(int *) p = param1;
    *(int *) (p + 4) = 1;
    *(int *) (p + 0x24) = result2;
    *(int *) (p + 8) = result1;
    *(char *) (p + 0x5d) = (signed char) data_020d2bb9[result1 << 4];
    if (param3) {
        *(int *) (p + 0x34) = param3[0];
        *(int *) (p + 0x38) = param3[1];
        *(int *) (p + 0x3c) = param3[2];
    }
    func_020bf810(p, param4);
    (*(int *) (work + 0x2f14))++;
done:
    return p;
}