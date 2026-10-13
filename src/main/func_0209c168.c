/* func_0209c168 @ 0x0209c168, 0x56 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x10];
    unsigned char b;
    char str[1];
} UnkStruct_0209c168;

extern int func_0209c38c(int);
extern int func_0209c4a8(const char *);
extern int func_0209c410(const char *, int);
extern void func_0209c470(const char *, int _x);
extern void func_0209c270(UnkStruct_0209c168 *);

int func_0209c168(UnkStruct_0209c168 *p)
{
    int v;

    if (func_0209c38c(p->b) != 0) {
        v = func_0209c4a8(p->str);
        if (func_0209c38c(v) != 0) {
            if (func_0209c410(p->str, v) == 0xff) {
                if (p->b == v) {
                    func_0209c470(p->str, p->b);
                    return p->b;
                } else {
                    func_0209c270(p);
                    return 8;
                }
            }
        }
    }
    return 0xc;
}