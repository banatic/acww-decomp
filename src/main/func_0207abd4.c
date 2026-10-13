/* func_0207abd4 @ 0x0207abd4, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[0x7ec];
} UnkStruct_0207abd4;

extern int func_0208150c(UnkStruct_0207abd4 *p);
extern int func_02003704(int x);
extern UnkStruct_0207abd4 *func_0207f270(UnkStruct_0207abd4 *p);
extern void func_020794c0(UnkStruct_0207abd4 *p, int x);
extern void func_020794a4(UnkStruct_0207abd4 *p, int x);

void func_0207abd4(UnkStruct_0207abd4 *arr)
{
    int i;
    int a = 0;
    int b = 0;
    for (i = 0; i < 8; i++) {
        UnkStruct_0207abd4 *p = &arr[i];
        if (func_02003704(func_0208150c(p))) {
            UnkStruct_0207abd4 *q;
            q = func_0207f270(p);
            func_020794c0(q, a);
            q = func_0207f270(p);
            func_020794a4(q, b);
        }
    }
}
