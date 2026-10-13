/* func_02024078 @ 0x02024078, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} Pair;

extern void func_020240a8(void);
extern void func_020157d4(void *, void (*)(void), int, int);
extern void func_02015828(void *, int);
extern int func_0202dbf0(void *, Pair);
extern Pair data_020d9118;

int func_02024078(void *p)
{
    func_020157d4(p, func_020240a8, 13, 0);
    func_02015828(p, 0);
    return func_0202dbf0(p, data_020d9118);
}
