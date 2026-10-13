/* func_ov004_02233c44 @ 0x02233c44, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02233c44 {
    int a;
    ~UnkStruct_02233c44() {}
};
extern "C" {
extern void *data_021c80bc;
extern void *data_021c67a4;
extern void func_ov004_02233c78(void *, void *, void *);
extern void func_ov004_022336f0(void *);
extern char data_ov004_02258af4;
}

extern "C" int func_ov004_02233c44(void *x)
{
    UnkStruct_02233c44 t;
    void *a = data_021c80bc;
    void *b = data_021c67a4;
    if (a != 0 && b != 0) {
        func_ov004_02233c78(x, a, b);
        func_ov004_022336f0(&data_ov004_02258af4);
    }
    return 1;
}
