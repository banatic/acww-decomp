/* func_ov003_0220d444 @ 0x0220d444, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020109fc(void *, int, int, int);
extern void func_ov003_0220d490(void *, int, int);

typedef struct {
    unsigned char x;
    unsigned char y;
} Pair;
typedef struct {
    char pad_00[0xc];
    unsigned char x;
    unsigned char y;
} UnkStruct_0220d444;

void func_ov003_0220d444(void *p, UnkStruct_0220d444 *b)
{
    Pair *s = (Pair *) ((char *) b + 0xc);
    Pair *d = (Pair *) ((char *) p + 0x7d4);
    unsigned char a = s->x;
    unsigned char c = s->y;
    if (c == 0) {
        func_020109fc(p, 0, 3, 3);
    }
    d->x = a;
    d->y = c;
    func_ov003_0220d490((char *) p + 0x8f0, a, c);
}
