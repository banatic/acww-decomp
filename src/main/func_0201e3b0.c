/* func_0201e3b0 @ 0x0201e3b0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
} Pair;
extern Pair data_020d8f98;
extern int func_02015590(int a, int b);
extern void func_0202dbf0(int a, Pair p);

void func_0201e3b0(int a)
{
    func_02015590(a, 0);
    func_0202dbf0(a, data_020d8f98);
}
