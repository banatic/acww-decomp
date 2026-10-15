/* func_020771cc @ 0x020771cc, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef void (*FnPtr)(int, void *, int);
extern FnPtr data_020cd2f4[];

extern int data_020ccf94;
extern int func_020738b4(int p0, int p1);
extern int func_0207762c(unsigned int r0);
extern int func_020738bc(int param1, int param2);
extern void func_020738ac(int p0, int p1, int p2);
extern int func_02064344(int dest, void *src, int size);
extern void MI_CpuCopy8(void *dest, const void *src, int size);

void func_020771cc(int a, void *out, int c, int d)
{
    int g = data_020ccf94;
    int b1 = func_020738b4(g, a);
    int bVal = func_0207762c(a);
    int cVal = func_020738bc(g, a);

    if (b1 == 0 && d == 0) {
        MI_CpuCopy8((void *) cVal, *(void **) ((char *) g + 0x70), bVal);
    }

    data_020cd2f4[a]((int) cVal, out, c);

    if (d != 0) {
        func_020738ac(g, a, 1);
    } else if (b1 != 0) {
        // nothing
    } else {
        int result;
        g = data_020ccf94;
        result = func_02064344(cVal, *(void **) ((char *) g + 0x70), bVal);
        func_020738ac(g, a, result);
    }
}
