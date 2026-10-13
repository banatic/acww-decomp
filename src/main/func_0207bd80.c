/* func_0207bd80 @ 0x0207bd80, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern void func_0209dfd8(void *dst, const void *src, int c, int d, int e);
extern void func_0209e474(void *);
extern int func_0209e3ac(void *a, void *b, int n);
extern void func_0207f5e4(void *p);
extern void func_0209df64(void *p);

typedef struct {
    unsigned int unk_00;
    unsigned int w1;
} Pair;

void func_0207bd80(void *obj)
{
    Pair a;
    Pair b;
    char *p;
    int i;

    func_0209dfd8(&a, (char *) obj + 0x407a, 0, 0, 0);
    b.unk_00 = 0;
    b.w1 = 0;
    func_0209e474(&b);
    if (func_0209e3ac(&b, &a, 0x38) != 0) {
        p = (char *) obj;
        i = 0;
        do {
            func_0207f5e4(p);
            p += 0x7ec;
            i++;
        } while (i < 8);
        func_0209df64((char *) obj + 0x407a);
    }
}
