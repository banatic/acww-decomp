/* func_0207c9b8 @ 0x0207c9b8, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207ca08(void *);
extern int func_0208150c(void *b);
extern int func_02003704(int t);
extern int func_02003648(int t);
extern void func_0207ca74(void *a, int x);
extern void MI_CpuFill8(void *dst, int val, int len);

typedef struct {
    unsigned char data[2028];
} TypeB;

typedef struct {
    unsigned char data[20];
} TypeA;

void func_0207c9b8(TypeA *a, TypeB *b)
{
    int i, t;

    if (func_0207ca08(a)) {
        MI_CpuFill8(a, 0, 20);
        for (i = 0; i < 8; i++) {
            t = func_0208150c(b);
            if (func_02003704(t)) {
                func_0207ca74(a, func_02003648(t));
            }
            b++;
        }
    }
}
