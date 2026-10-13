/* func_0205fe24 @ 0x0205fe24, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02034270(void *dst, void *src, int a, int b);
extern void func_0203423c(void *ptr);

void func_0205fe24(void *arg)
{
    struct {
        char pad[0x30];
        int field_30;
        char pad2[0x8];
        int field_3c;
    } local;
    int tmp;
    int *p = (int *) arg;

    func_02034270(&local, (char *) arg + 8, 1, 1);
    if (local.field_30 != 0) {
        tmp = local.field_3c - 0x333;
        if (p[3] > tmp) {
            p[3] = p[3] - 0x19a;
        } else {
            p[3] = tmp;
        }
    }
    func_0203423c(&local);
}
