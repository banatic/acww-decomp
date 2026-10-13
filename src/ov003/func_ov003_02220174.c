/* func_ov003_02220174 @ 0x02220174, 0x70 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov003_0223cef0[];
extern void *func_ov009_02262fcc(void *);
extern int func_0204bcdc(void *);
extern int func_0204bc64(void *);

static __inline int predA(void *q, unsigned short key)
{
    unsigned short tmp;
    tmp = key;
    if (func_0204bc64(q) == func_0204bc64(&tmp)) {
        return 1;
    }
    return 0;
}

static __inline int predB(void *q, unsigned short key)
{
    if (*(unsigned short *) q == key) {
        return 1;
    }
    return 0;
}

void *func_ov003_02220174(unsigned short key)
{
    unsigned int i;
    void *e;
    void *q;
    int v;
    for (i = 0; i < 0x20; i++) {
        e = data_ov003_0223cef0[i];
        if (e != 0) {
            q = func_ov009_02262fcc(e);
            if (func_0204bcdc(q) != 0) {
                v = predA(q, key);
            } else {
                v = predB(q, key);
            }
            if (v != 0) {
                return e;
            }
        }
    }
    return 0;
}
