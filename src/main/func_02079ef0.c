/* func_02079ef0 @ 0x02079ef0, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x7ec];
} Entry;

extern int func_0207918c(void);
extern int func_0207cf74(int c);
extern int func_02003704(void *p);
extern void *func_0208150c(void *p);

void func_02079ef0(int unused, signed char *out, int *count, signed char *list, Entry *table)
{
    int neg = -1;
    int zero = 0;
    int i;
    int v;

    v = func_0207918c();
    if (func_0207cf74(v)) {
        for (i = 0; i < 8; i++) {
            signed char c = list[zero];
            if (func_0207cf74(c)) {
                if (c == v) {
                    if (func_02003704(func_0208150c(&table[c]))) {
                        out[*count] = c;
                        *count = *count + 1;
                    }
                    *list = neg;
                }
            }
            list++;
        }
    }
}
