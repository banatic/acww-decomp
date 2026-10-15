/* func_02080108 @ 0x02080108, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020807a8(int a, int b);
extern void func_02081ac8(void *object, void *source, int count);

void func_02080108(int p1, int p2, int p3, int p4)
{
    int ret = func_020807a8(p1, p4);
    if (ret != 0) {
        func_02081ac8((void *) ret, (void *) p2, p3);
    }
}
