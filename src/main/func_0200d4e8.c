/* func_0200d4e8 @ 0x0200d4e8, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int data[3];
} UnkStruct_0200d4e8;

typedef struct {
    unsigned int data[4];
} UnkStruct_0200d4e8_2;

extern void func_0200e92c(UnkStruct_0200d4e8 *);
extern void func_0200e90c(UnkStruct_0200d4e8 *, int, int, int);
extern void func_0200d528(UnkStruct_0200d4e8_2 *, int);
extern int func_0200e894(void *, UnkStruct_0200d4e8 *);
extern void func_0200e91c(UnkStruct_0200d4e8 *);

int func_0200d4e8(void *p, int n, int a, int b)
{
    UnkStruct_0200d4e8 s1;
    UnkStruct_0200d4e8_2 s2;
    int res;

    func_0200e92c(&s1);
    func_0200e90c(&s1, 2, a, b);
    func_0200d528(&s2, n);
    res = func_0200e894(p, &s1);
    func_0200e91c(&s1);
    return res;
}
