/* func_0200b7e8 @ 0x0200b7e8, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern void func_0200b894(void *, int *, int, int, int);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);

typedef struct {
    int a;
    short b;
} UnkStruct_0200b7e8;

int func_0200b7e8(void *p0, int *p1, int p2, int p3, int p4, short p5)
{
    int pair[2];
    char obj[12];
    char tmp[16];
    int result;

    func_0200e92c(obj);
    func_0200e90c(obj, 0x19, p4, p5);
    pair[0] = p1[0];
    pair[1] = p1[1];
    func_0200b894(tmp, pair, -1, p2, p3);
    result = func_0200e894(p0, obj);
    func_0200e91c(obj);
    return result;
}
