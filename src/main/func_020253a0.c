/* func_020253a0 @ 0x020253a0, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} Pair;
extern int func_02015094(int arg);
extern void func_0202dbf0(int arg, Pair p);
extern Pair data_020d9230;

void func_020253a0(int arg, int event)
{
    func_02015094(arg);
    func_0202dbf0(arg, data_020d9230);
}
