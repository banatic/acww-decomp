/* func_020ede60 @ 0x020ede60, 0x68 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct Pair {
    unsigned lo;
    unsigned hi;
};
extern struct Pair data_0213e77c;
extern struct Pair data_0213e78c;
extern struct Pair data_0213e794;
extern int func_01ffd44c(int, struct Pair, struct Pair, struct Pair);

void func_020ede60(int a)
{
    func_01ffd44c(a, data_0213e794, data_0213e78c, data_0213e77c);
}
