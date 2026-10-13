/* func_02011dd0 @ 0x02011dd0, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
} Mgr;

extern Mgr data_021c1284;

extern void func_02011d28(Mgr *o);
extern int func_02011c28(Mgr *o, int a);
extern void func_02011b38(Mgr *o, int b);
extern void func_02011bb0(Mgr *o);
extern int func_02011a58(Mgr *o, int a);
extern void func_020119c4(Mgr *o, int b);
extern void func_02011a50(Mgr *o);
extern int func_02011ed4(void);
extern int func_0208ff98(void);
extern void func_02011d90(void *p, int a, int b, int c);

void func_02011dd0(void *p, int a, int b)
{
    Mgr *o;

    o = &data_021c1284;
    func_02011d28(o);
    if (func_02011c28(o, a)) {
        func_02011b38(o, b);
    }
    func_02011bb0(o);
    if (func_02011a58(o, a)) {
        func_020119c4(o, b);
    }
    func_02011a50(o);
    if ((a == 2 || (a == 4 && func_02011ed4() == 2)) && func_0208ff98()) {
        func_02011d90(p, 1, 0, b);
    }
}
