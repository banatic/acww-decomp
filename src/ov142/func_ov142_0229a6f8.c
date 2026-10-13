/* func_ov142_0229a6f8 @ 0x0229a6f8, 0x74 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short id;
    unsigned short unk_02;
    int unk_04;
} Key;

extern void *func_020984e8(void);
extern int func_0204c2b4(Key *);
extern void *func_020996ac(void *);
extern int func_0203cdcc(void *, Key *);

int func_ov142_0229a6f8(short *a, unsigned short *out, unsigned short id, int count, int base)
{
    Key key;
    void *h;
    int n;
    int i;
    short *p;

    n = 0;
    key.id = 0xfff1;
    h = func_020984e8();
    i = 0;
    p = a + base;
    for (; i < count; i++) {
        key.id = id;
        if (func_0204c2b4(&key) != 0) {
            *(short *) ((char *) p + 0xd6) = (short) (*(short *) ((char *) p + 0xd6) + 1);
            if (func_0203cdcc(func_020996ac(h), &key) != 0) {
                out[n] = id;
                n++;
            }
        }
        id = (unsigned short) (id + 1);
    }
    return n;
}
