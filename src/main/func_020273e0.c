/* func_020273e0 @ 0x020273e0, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int x;
    unsigned int y;
} TwoWords;

extern int func_02015094(unsigned int arg);
extern void func_0202dbdc(unsigned int arg, TwoWords pair);
extern TwoWords data_020d9068;

void func_020273e0(unsigned int arg)
{
    func_02015094(arg);
    func_0202dbdc(arg, data_020d9068);
}
