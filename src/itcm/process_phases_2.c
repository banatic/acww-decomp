/* process_phases_2: 2 functions, module itcm
 * mwccarm 1.2/base -O4,s
 * func_01ffd14c @ 0x01ffd14c, 0x68 bytes, ARM
 * func_01ffd0e4 @ 0x01ffd0e4, 0x68 bytes, ARM
 */

struct Pair {
    unsigned lo;
    unsigned hi;
};

extern struct Pair data_01ffd0b4;
extern struct Pair data_01ffd0d4;
extern struct Pair data_01ffd0cc;
extern int func_01ffd44c(int, struct Pair, struct Pair, struct Pair);
extern struct Pair data_01ffd0dc;
extern struct Pair data_01ffd0c4;
extern struct Pair data_01ffd0bc;

void func_01ffd14c(int a)
{
    func_01ffd44c(a, data_01ffd0cc, data_01ffd0d4, data_01ffd0b4);
}

void func_01ffd0e4(int a)
{
    func_01ffd44c(a, data_01ffd0bc, data_01ffd0c4, data_01ffd0dc);
}
