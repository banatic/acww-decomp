/* town_villager: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02080998 @ 0x02080998, 0x94 bytes, Thumb
 * func_02080928 @ 0x02080928, 0x70 bytes, Thumb
 */

typedef struct {
    unsigned short id;
    unsigned char pad_02[10];
} Entry;

extern int func_0208150c(const void *self);
extern int func_02003704(int);
extern int func_0207f294(const void *self);
extern void func_0209e474(unsigned char *p);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int n);
extern int func_0203fea0(void *dst, const void *src);
extern void func_0209e29c(unsigned char *p, int n);
extern char *func_0204c7c0(void);
extern void *func_0207b3dc(void *p);
extern void *func_020984e8(void);
extern int func_0207f150(void *p);
extern char *func_02099640(void *a);
extern int func_0209aebc(char *m, int h);

int func_02080998(const void *self, int n, const void *param)
{
    unsigned char date[8];
    unsigned char tmp[8];
    Entry entries[7];
    int v;
    int i, k, count;
    Entry *e;

    if (func_02003704(func_0208150c(self)) == 0) {
        goto fail;
    }
    if (func_0207f294(self) == -1) {
        goto fail;
    }
    v = func_0207f294(self);

    ((int *) date)[0] = 0;
    ((int *) date)[1] = 0;
    if (param == 0) {
        func_0209e474(date);
    } else {
        MI_CpuCopy8(param, date, 8);
    }

    for (i = 0; i <= n; i++) {
        e = entries;
        MI_CpuCopy8(date, tmp, 8);
        count = func_0203fea0(e, tmp);
        k = 0;
        while (k < count) {
            if (e->id == v) {
                return date[5];
            }
            e++;
            k++;
        }
        func_0209e29c(date, 1);
    }
fail:
    return -1;
}

int func_02080928(void *p0)
{
    int ok;
    void *e;
    void *a;
    char *m;

    if (func_02003704(func_0208150c((const void *) p0)) == 0) {
        goto zero;
    }
    e = func_0207b3dc(func_0204c7c0() + 0x9284);
    a = func_020984e8();
    ok = 0;
    if (e == (void *) func_0207f294((const void *) p0)) {
        goto ret;
    }
    if (func_0207f150(p0) != 3) {
        goto ret;
    }
    if (a == 0) {
        goto ret;
    }
    m = func_02099640(a);
    m = m + 0xa4;
    if (func_0209aebc(m, func_0208150c((const void *) p0)) != 0) {
        goto ret;
    }
    ok = 1;
ret:
    return ok;
zero:
    return 0;
}
