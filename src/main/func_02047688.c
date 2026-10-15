/* func_02047688 @ 0x02047688, 0xa8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00, w1;
} Pair;

extern unsigned char data_021f3a50[];
extern char data_021dc7a8[];

extern int func_0203fae4(void);
extern int func_020984e8(void);
extern void func_0209df38(Pair *p);
extern void func_0209e100(Pair *p, int n);
extern void func_020477e4(void *a0, void *a1, int a2, int a3, char *g);
extern void func_0204790c(void *a0, void *a1, int a2, int a3, int a4, void *a5, char *g);
extern void func_02047730(void *a0, void *a5);
extern void func_02047898(void *a0, char *g, void *a5);

void func_02047688(void *a0, void *a1, int a2, int a3, int a4, void *a5)
{
    Pair a;
    unsigned char *g;

    if (func_0203fae4() != 0) {
        if (a5 == 0) {
            return;
        }
        if (func_020984e8() != 0) {
            return;
        }
    }
    a.unk_00 = 0;
    a.w1 = 0;
    func_0209df38(&a);
    func_0209e100(&a, 6);
    g = data_021f3a50;
    if (g[2] != ((unsigned char *) &a)[5] || g[1] != ((unsigned char *) &a)[4] || g[0] != ((unsigned char *) &a)[3]) {
        func_020477e4(a0, a1, a2, a3, data_021dc7a8);
        func_0204790c(a0, a1, a2, a3, a4, a5, data_021dc7a8);
        g[2] = ((unsigned char *) &a)[5];
        g[1] = ((unsigned char *) &a)[4];
        g[0] = ((unsigned char *) &a)[3];
    }
    func_02047730(a0, a5);
    func_02047898(a0, data_021dc7a8, a5);
}
