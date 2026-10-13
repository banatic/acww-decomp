/* func_02023634 @ 0x02023634, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct Pair {
    int a;
    int b;
} data_020d9090;
extern void func_020157c8(void *p, int a, int b);
extern void func_02015828(void *p, int a);
extern int func_0202dbf0(void *p, struct Pair pair);

int func_02023634(void *arg0)
{
    func_020157c8(arg0, 0x31, 0);
    func_02015828(arg0, 2);
    return func_0202dbf0(arg0, data_020d9090);
}
