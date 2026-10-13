/* func_01ffd0e4 @ 0x01ffd0e4, 0x68 bytes, ARM, module itcm
 * mwccarm 1.2/base -O4,s
 */

struct Pair {
    unsigned lo;
    unsigned hi;
};
extern struct Pair data_01ffd0dc;
extern struct Pair data_01ffd0c4;
extern struct Pair data_01ffd0bc;
extern void func_01ffd44c(int, struct Pair, struct Pair, struct Pair);

void func_01ffd0e4(int a)
{
    func_01ffd44c(a, data_01ffd0bc, data_01ffd0c4, data_01ffd0dc);
}
