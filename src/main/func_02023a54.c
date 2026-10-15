/* func_02023a54 @ 0x02023a54, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099734(int);
extern int func_02098eb8(int);
extern int func_020154b4(void *, void *, int, int, int);
extern int func_02098f0c(int, void *, int, int);
extern int func_020996ac(int);
extern int OSi_DoUnlockByWord__main_0203cd2c(int, void *, int, int);

typedef struct {
    int a;
    int b;
} Pair;

extern Pair data_020d90e0;

extern void func_0202dbf0(void *, Pair);

void func_02023a54(void *obj)
{
    int a;
    int b;
    int c;
    int d;

    a = func_020984e8();
    b = func_02099734(a);
    c = func_02098eb8(b);
    if (c == -1) {
        c = 0;
    }
    func_020154b4(obj, (char *) obj + 0x19c, 0, 5, 0);
    func_02098f0c(b, (char *) obj + 0x19c, c, 0);
    d = func_020996ac(a);
    OSi_DoUnlockByWord__main_0203cd2c(d, (char *) obj + 0x19c, 0, 1);
    func_0202dbf0(obj, data_020d90e0);
}
