/* func_02027ff8 @ 0x02027ff8, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
} Pair;

extern int func_0202d9c4(void *);
extern int func_0209bc40(int);
extern void func_02015330(void *, void *, int, int, int);
extern void func_0202dbf0(void *, Pair);
extern void func_0209b56c(int);
extern Pair data_020d90b8;

void func_02027ff8(void *arg)
{
    if (func_0209bc40(func_0202d9c4(arg)) == 10) {
        func_02015330(arg, (char *) arg + 0x124, 2, 5, 0);
        func_0202dbf0(arg, data_020d90b8);
    }
    func_0209b56c(*(int *) ((char *) arg + 0x160));
}
