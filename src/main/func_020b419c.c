/* func_020b419c @ 0x020b419c, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b4c0c(void *ptr);
extern void func_020a94a4(void *ptr);
extern void func_020a9354(void *ptr, int x);
extern int func_020a92d8(void *, int);
extern int func_020b4bb4(void *ptr);
extern int func_020b4178(int a, int b);

int func_020b419c(char *p);
int func_020b419c(char *p)
{
    int count;
    char *base;
    int val;

    count = 0;
    func_020b4c0c(p + 0x18f4);
    func_020a94a4(p + 0x1934);
    func_020a9354(p + 0x1934, *(int *) (p + 0x1958));

    base = p + 0x18f4;

    while (1) {
        *(int *) (p + 0x195c) = 1;
        *(int *) (p + 0x1960) = 0;

        func_020a92d8(p + 0x1934, 0);

        val = *(int *) (p + 0x1960);
        if (val == 0xa || val == 0) {
            break;
        }

        if (func_020b4178(func_020b4bb4(base), val) != 0) {
            count++;
        } else {
            count = 0;
            break;
        }
    }

    return count;
}
