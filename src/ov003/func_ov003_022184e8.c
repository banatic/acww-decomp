/* func_ov003_022184e8 @ 0x022184e8, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020109a0(void *, int, int, int);
extern void func_0200fbc4(void *, int, int, int);

typedef struct {
    int a;
    int b;
    short c;
    unsigned char d;
    unsigned char cnt;
} UnkStruct_022184e8;

void func_ov003_022184e8(void *p)
{
    UnkStruct_022184e8 *s = (UnkStruct_022184e8 *) ((char *) p + 0x7d4);
    unsigned char *q = &s->cnt;
    if (s->cnt != 0) {
        *q = (unsigned char) (s->cnt - 1);
        if (*q == 0) {
            func_020109a0(p, 0x33, 3, 0);
        }
    } else {
        func_0200fbc4(p, s->a, s->b, s->c);
    }
}
