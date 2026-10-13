/* func_0200fd04 @ 0x0200fd04, 0xca bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Pair {
    int x;
    int y;
} Pair;

extern int func_0200ffec(void);
extern void func_0204f818(int *, int *, int);
extern void func_ov004_0222ac24(int, Pair *, int, int, int);
extern void func_0200bdbc(int, Pair *, int, int, int);
extern void func_ov003_02218ec4(int, Pair *, int, int);
extern void func_ov003_022100c4(int, Pair *, int, int, int);

int func_0200fd04(int a, int b, int c)
{
    int id = func_0200ffec();
    int v0 = 0;
    int v1 = 0;

    func_0204f818(&v0, &v1, b);

    switch (id) {
        case 3:
        case 4:
        case 21:
        case 22:
            if (c) {
                Pair tmp;
                tmp.x = v0;
                tmp.y = v1;
                func_ov004_0222ac24(a, &tmp, -2, 6, -1);
            } else {
                Pair tmp;
                tmp.x = v0;
                tmp.y = v1;
                func_0200bdbc(a, &tmp, -1, 6, -1);
            }
            return 1;
        case 5: {
            Pair tmp;
            tmp.x = v0;
            tmp.y = v1;
            func_ov003_02218ec4(a, &tmp, 6, -1);
        }
            return 1;
        case 20: {
            Pair tmp;
            tmp.x = v0;
            tmp.y = v1;
            func_ov003_022100c4(a, &tmp, 0, 6, -1);
        }
            return 1;
        default:
            return 0;
    }
}
