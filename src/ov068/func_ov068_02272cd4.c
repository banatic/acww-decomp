/* func_ov068_02272cd4 @ 0x02272cd4, 0x48 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct Triple {
    int a;
    int b;
    int c;
};
struct Res {
    int unk_00;
    int pad_04;
    int v1;
};
struct Params {
    int unk_00;
    int p1;
    int p2;
    int p3;
};

extern struct Triple *func_02095794(int);
extern void func_ov068_02272d1c(void *, int);
extern void func_020eaca0(void *, void *, void *);
extern int func_020e8ed8(int, int);

int func_ov068_02272cd4(int arg0)
{
    if (func_02095794(4) != 0) {
        struct Triple *p = func_02095794(4);
        struct Triple src;
        struct Res res;
        struct Params params;
        src.a = p->a;
        src.b = p->b;
        src.c = p->c;
        func_ov068_02272d1c(&params, arg0);
        func_020eaca0(&res, &params, &src);
        return func_020e8ed8(res.unk_00, res.v1);
    } else {
        return 0;
    }
}
