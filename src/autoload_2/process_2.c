/* process_2: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020ede60 @ 0x020ede60, 0x68 bytes, ARM
 * func_020edddc @ 0x020edddc, 0x84 bytes, ARM
 */

struct Pair {
    unsigned lo;
    unsigned hi;
};

typedef struct {
    int x, y;
} Pair;

typedef struct {
    char pad_00[12];
    unsigned short unk_0C;
} Input;

extern struct Pair data_0213e77c;
extern struct Pair data_0213e78c;
extern struct Pair data_0213e794;
extern int func_01ffd44c(int, struct Pair, struct Pair, struct Pair);
extern Pair data_0213e7a4; // 0x0213e7a4
extern Pair data_0213e79c; // 0x0213e79c
extern Pair data_0213e784; // 0x0213e784
extern void func_020edbec(unsigned short v);

void func_020ede60(int a)
{
    func_01ffd44c(a, data_0213e794, data_0213e78c, data_0213e77c);
}

int func_020edddc(Input *p)
{
    unsigned short v = p->unk_0C;
    int result = func_01ffd44c((int) p, *(struct Pair *) &data_0213e784, *(struct Pair *) &data_0213e79c, *(struct Pair *) &data_0213e7a4);
    if (result == 1) {
        func_020edbec(v);
    }
    return result;
}
