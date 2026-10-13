/* func_020200cc @ 0x020200cc, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int a;
    unsigned int b;
} Pair;

extern int func_02015774(int, int, const void *, int, int);
extern int func_02015828(int, int);
extern int func_0202dbf0(int, Pair);
extern Pair data_020d9310;

extern unsigned char data_021c1e84[];

int func_020200cc(int param)
{
    func_02015774(param, 23, (const void *) data_021c1e84, 10, 0);
    func_02015828(param, 6);
    return func_0202dbf0(param, data_020d9310);
}
