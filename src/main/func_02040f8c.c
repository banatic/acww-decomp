/* func_02040f8c @ 0x02040f8c, 0x8e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02041110(void *p0, int *p1, int n);
extern int func_0204105c(void *p0, unsigned char *p3);
extern void *func_020409c8(void *p0, int n);
extern void func_0209e29c(void *buf, int n);
extern void func_020408b8(void *ptr, unsigned char byte, void *buf2);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int n);

typedef struct {
    int a;
    int b;
} Pair;

void func_02040f8c(void *p0, int *p1, int *counter, unsigned char *p3, const void *p4)
{
    int i = 0;
    int local0 = 0;
    void *ptr;
    int local1 = 0;
    int idx;
    int val;
    Pair tmp1, tmp2;

    for (; i < 2; i++) {
        val = 0x63;
        if (*counter > 0) {
            idx = func_02041110(p0, p1, *counter);
            if (idx >= 0) {
                val = func_0204105c(p0, p3);
                p1[idx] = local0;
                (*counter)--;
            }
            ptr = func_020409c8(p0, idx + 1);
            if (ptr != 0) {
                tmp1.a = local1;
                tmp1.b = local1;
                MI_CpuCopy8(p4, &tmp1, 8);
                func_0209e29c(&tmp1, idx + 1);
                MI_CpuCopy8(&tmp1, &tmp2, 8);
                func_020408b8(ptr, (unsigned char) val, &tmp2);
            }
        }
        p3[5] = (unsigned char) val;
    }
}