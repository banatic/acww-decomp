/* func_0203b174 @ 0x0203b174, 0x3e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203be6c(void *p);
extern void func_01ffcbb0(char *buf, void *p);
extern int func_0203c57c(void *p);
extern int func_0203c568(void *p);
extern int func_0203c548(void *p);
extern void func_0203bd84(void *p, char *buf, int a, int b, int c);

void func_0203b174(void *p)
{
    int stackArg;
    char buf[12];
    int v1, v2;
    func_0203be6c(p);
    func_01ffcbb0(buf, p);
    v1 = func_0203c57c(p);
    v2 = func_0203c568(p);
    stackArg = func_0203c548(p);
    func_0203bd84(p, buf, v1, v2, stackArg);
}
