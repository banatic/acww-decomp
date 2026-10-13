/* func_0207ef54 @ 0x0207ef54, 0x11e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char *func_0208150c(void *p);
extern int func_02003704(const void *p);
extern char *func_0209ad9c(void *p, int i);
extern void *func_0209b4d4(const void *p);
extern int func_0209bd44(void *p);
extern char *func_0209b4cc(const void *p, int data);
extern int memcmp(const void *a, const void *b, int n);
extern int func_0209a854(void *p, char *key);
extern int func_0209aebc(void *p, char *key);

static inline int eq(const char *t, const char *key)
{
    return *(const unsigned short *) t == *(const unsigned short *) key && memcmp(t + 2, key + 2, 12) == 0 &&
           *(const unsigned char *) (t + 0xf) == *(const unsigned char *) (key + 0xf);
}

int func_0207ef54(void *a0, char *obj)
{
    char *key;
    char *e0;
    char *e1;
    char *q;

    key = func_0208150c(a0);
    if (func_02003704(key) != 0) {
        e0 = func_0209ad9c(obj, 0);
        e1 = func_0209ad9c(obj, 1);
        q = obj;
        q = obj + 0xa4;
        if (func_0209bd44(func_0209b4d4(e0)) != 0) {
            if (eq(func_0209b4cc(e0, 0), key) || eq(func_0209b4cc(e0, 1), key)) {
                return 1;
            }
        }
        if (func_0209bd44(func_0209b4d4(e1)) != 0) {
            if (eq(func_0209b4cc(e1, 0), key) || eq(func_0209b4cc(e1, 1), key)) {
                return 1;
            }
        }
        if (func_0209a854(obj, key) != 0) {
            return 1;
        }
        if (func_0209aebc(q, key) != 0) {
            return 1;
        }
    }
    return 0;
}
