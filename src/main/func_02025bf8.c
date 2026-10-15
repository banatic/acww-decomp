/* func_02025bf8 @ 0x02025bf8, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202d9c4(int arg);
extern int func_0209bc40(int value);
extern void func_020157d4(void *, int (*)(unsigned short *, int), unsigned char, unsigned char);
extern int func_02015828(int arg, int a);

typedef struct {
    int unk_00;
    int unk_04;
} Pair;

extern Pair data_020d92f0;
extern void func_0202dbf0(int arg, Pair value);
extern unsigned short func_0202a17c(unsigned short *, int);
extern unsigned short func_0202a12c(unsigned short *, int);

#define Predicate_0202a17c ((int (*)(unsigned short *, int)) func_0202a17c)

#define Predicate_0202a12c ((int (*)(unsigned short *, int)) func_0202a12c)

void func_02025bf8(int arg)
{
    if (func_0209bc40(func_0202d9c4(arg)) == 0) {
        func_020157d4((void *) arg, Predicate_0202a17c, 13, 1);
    } else {
        func_020157d4((void *) arg, Predicate_0202a12c, 13, 1);
    }
    func_02015828(arg, 0);
    func_0202dbf0(arg, data_020d92f0);
}
