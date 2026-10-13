/* func_0202a8a4 @ 0x0202a8a4, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int a;
    unsigned int b;
} Pair;

extern char data_021c1e84[];
extern Pair data_020d9178;

extern void MI_CpuFill8(void *dst, int fill, int len);
extern void func_02015774(void *a, int b, void *c, int d, int e);
extern void func_02015828(void *a, int b);
extern void func_0202dbf0(void *a, Pair arg);

void func_0202a8a4(void *p)
{
    MI_CpuFill8(data_021c1e84, 0, 0x40);
    func_02015774(p, 0x11, data_021c1e84, 6, 0);
    func_02015828(p, 6);
    func_0202dbf0(p, data_020d9178);
}
