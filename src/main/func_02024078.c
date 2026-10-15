/* func_02024078 @ 0x02024078, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} Pair;

extern int func_020240a8(unsigned short *, int);
extern void func_020157d4(void *, int (*)(unsigned short *, int), unsigned char, unsigned char);
extern int func_02015828(void *, int);
extern void func_0202dbf0(void *, Pair);
extern Pair data_020d9118;

void func_02024078(void *p, void *output)
{
    func_020157d4(p, func_020240a8, 13, 0);
    func_02015828(p, 0);
    func_0202dbf0(p, data_020d9118);
}
