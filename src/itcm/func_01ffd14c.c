/* func_01ffd14c @ 0x01ffd14c, 0x68 bytes, ARM, module itcm
 * mwccarm 1.2/base -O4,s
 */

struct Pair {
    unsigned lo;
    unsigned hi;
};
extern struct Pair data_01ffd0b4;
extern struct Pair data_01ffd0d4;
extern struct Pair data_01ffd0cc;
extern void func_01ffd44c(int, struct Pair, struct Pair, struct Pair);

void func_01ffd14c(int a)
{
    func_01ffd44c(a, data_01ffd0cc, data_01ffd0d4, data_01ffd0b4);
}
