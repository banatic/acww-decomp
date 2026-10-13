/* func_02080998 @ 0x02080998, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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
