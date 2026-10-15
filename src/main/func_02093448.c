/* func_02093448 @ 0x02093448, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02034270(void *, int, int, int);
extern void func_0203423c(void *);
extern int func_020b6598(void);
extern int func_02094cf8(int, int, int, int, int, void *);
extern int data_020e29dc;

struct func_02093448_obj {
    unsigned char pad_00[0x34];
    int unk_34;
    unsigned char pad_38[0x8];
};

int func_02093448(int a, int b, int c, int d)
{
    struct func_02093448_obj obj;
    int st;
    int kind;
    int result;

    st = func_02034270(&obj, b, 0, 0);
    kind = obj.unk_34;

    if (kind == 0x13 || (func_020b6598() != 0 && kind == 3)) {
        result = func_02094cf8(0x55, a, b, c, d, &data_020e29dc);
        func_0203423c(&obj);
        return result;
    } else {
        func_0203423c(&obj);
        return 3;
    }
}
