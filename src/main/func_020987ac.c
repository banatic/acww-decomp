/* func_020987ac @ 0x020987ac, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short id;
    char data[0xc];
} Key;
typedef struct {
    char pad_00[0x249c];
} Elem;

extern int func_02098868(void *);
extern int func_02098880(void *);
extern int func_020644cc(int);
extern int func_02099a28(Elem *);
extern Key *func_02099870(Elem *);
extern int memcmp(const void *, const void *, int);
extern int func_0209518c(Key *, Key *);

void *func_020987ac(void *p0, Key *p1)
{
    void *result;
    int n, k, i;
    Elem *e;
    Key *q;

    if (p1 == 0 || func_02098868(p0) == 0) {
        n = func_02098880(p0);
    } else {
        n = func_02098880(p0) - 1;
    }
    result = 0;
    if (n > 0) {
        k = func_020644cc(n);
        for (i = 0; i < 4; i++) {
            e = (Elem *) ((char *) p0 + i * 0x249c);
            if (func_02099a28(e) == 1) {
                if (p1 != 0) {
                    q = func_02099870(e);
                    if (p1->id == q->id && memcmp(p1->data, q->data, 0xc) == 0 && func_0209518c(p1, q) != 0) {
                        continue;
                    }
                }
                if (k == 0) {
                    result = e;
                    break;
                }
                k--;
            }
        }
    }
    return result;
}
