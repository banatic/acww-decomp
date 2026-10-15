/* func_020251d0 @ 0x020251d0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} Pair;

extern int func_020154b4(int, int, int, int, int);
extern void func_0202dbf0(int, Pair);
extern Pair data_020d8f70;

void func_020251d0(int param)
{
    func_020154b4(param, param + 0x19c, 0, 5, 0);
    func_0202dbf0(param, data_020d8f70);
}
