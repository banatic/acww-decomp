/* func_02023634 @ 0x02023634, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct Pair {
    int a;
    int b;
} data_020d9090;
extern void func_020157c8(void *p, int a, int b);
extern int func_02015828(void *p, int a);
extern void func_0202dbf0(void *p, struct Pair pair);

void func_02023634(void *arg0, int event)
{
    func_020157c8(arg0, 0x31, 0);
    func_02015828(arg0, 2);
    func_0202dbf0(arg0, data_020d9090);
}
