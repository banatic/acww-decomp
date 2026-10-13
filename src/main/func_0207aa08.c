/* func_0207aa08 @ 0x0207aa08, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short id;
    unsigned char pad_02[10];
} Entry;

extern int func_020984e8(void);
extern int func_02099020(int, int);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int n);
extern int func_0203fea0(void *dst, const void *src);
extern int func_0208150c(const void *self);
extern int func_02003704(int);
extern int func_0207f150(const void *self);

int func_0207aa08(const void *self, const void *param)
{
    int a;
    int i, count;
    Entry *e;
    int k;
    unsigned char local8[8];
    Entry entries[7];

    a = func_020984e8();
    if (a == 0) {
        goto fail;
    }
    if (func_02099020(a, 1) != 0) {
        goto fail;
    }
    if (((const unsigned char *) param)[2] < 6) {
        goto fail;
    }

    MI_CpuCopy8(param, local8, 8);
    count = func_0203fea0(entries, local8);

    for (i = 0; i < 8; self = (const char *) self + 0x7ec, i++) {
        if (func_02003704(func_0208150c(self)) == 0) {
            continue;
        }
        if (func_0207f150(self) != 3) {
            continue;
        }
        e = entries;
        k = 0;
        while (k < count) {
            if (e->id == i) {
                return i;
            }
            e++;
            k++;
        }
    }
fail:
    return -1;
}