/* func_0200bdbc @ 0x0200bdbc, 0x4e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern void func_0200be0c(void *, void *, int);
extern int func_0200e894(void *, void *);
extern void func_0200e91c(void *);

typedef struct {
    int x;
    int y;
} Pair;

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_0200bdbc;

typedef struct {
    int d[4];
} Other;

int func_0200bdbc(void *p1, Pair *p2, int p3, int p4, short p5)
{
    Pair pair;
    UnkStruct_0200bdbc obj;
    Other other;
    int r;

    func_0200e92c(&obj);
    func_0200e90c(&obj, 0x18, p4, p5);
    pair.x = p2->x;
    pair.y = p2->y;
    func_0200be0c(&other, &pair, p3);
    r = func_0200e894(p1, &obj);
    func_0200e91c(&obj);
    return r;
}
