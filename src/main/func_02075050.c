/* func_02075050 @ 0x02075050, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02075050 UnkStruct_02075050;

extern UnkStruct_02075050 *data_020ccf94;

extern void DC_FlushAll(void);
extern int func_02077b20(char *p);
extern void func_02073cf0(UnkStruct_02075050 *g, int a, int t);
extern int func_02077b28(char *p);
extern int func_02077b14(char *p);
extern void func_02075240(char *a, unsigned int b, int c, int d);
extern void func_020731a4(UnkStruct_02075050 *g, int a);
extern int func_02073928(UnkStruct_02075050 *g, int a);
extern void func_02073bac(UnkStruct_02075050 *g, int a, int b, unsigned int c);
extern void func_0207399c(UnkStruct_02075050 *g, int a);
extern int func_02073c04(UnkStruct_02075050 *g, int a, int b);
extern void func_02073044(void);
extern void func_020ec338(unsigned short a, int b, int c);

void func_02075050(int a, char *p, unsigned int n)
{
    int t;
    UnkStruct_02075050 *g;
    int q;
    int v;

    DC_FlushAll();
    t = func_02077b20(p);
    if (t != 0) {
        func_02073cf0(data_020ccf94, a, t);
    }
    if (func_02077b28(p) != 0) {
        v = func_02077b14(p);
        if (v < 0x18) {
            func_02075240(p + 1, n - 1, a, v);
        }
    } else {
        func_020731a4(data_020ccf94, a);
        if (n > 1) {
            g = data_020ccf94;
            func_02073bac(g, a, func_02073928(g, a), n);
            func_0207399c(g, a);
            q = func_02073c04(g, a, func_02073928(g, a));
            func_02073044();
            func_020ec338((unsigned short) a, q, 0x1000);
        }
    }
}
