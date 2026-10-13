/* func_ov123_0229a180 @ 0x0229a180, 0x68 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov123_0229ae7c(int, int, int, int);
extern int func_ov123_0229ae74(int, int);
extern void func_020896b8(int, void *, int, int, int, int, int);

struct FuncOv123Data {
    unsigned short pad_00;
    unsigned short : 9;
    unsigned short field : 5;
    unsigned short : 2;
};

extern struct FuncOv123Data data_ov123_0229cf20;
extern const unsigned short data_ov123_0229cea0[];

void func_ov123_0229a180(int p0, int p1, int p2, int p3)
{
    int a;
    int b;
    unsigned short t;

    a = func_ov123_0229ae7c(p0, p1, p2, p3);
    b = func_ov123_0229ae74(p0, p2);
    t = data_ov123_0229cf20.field & ~0x18;
    t |= data_ov123_0229cea0[p3];
    data_ov123_0229cf20.field = t;
    func_020896b8(1, &data_ov123_0229cf20, a, b, -1, -1, 0);
}
