/* func_ov004_0222db58 @ 0x0222db58, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0222db58 {
    int a;
    ~UnkStruct_0222db58() {}
};

extern "C" {
extern int func_02054ecc(void *);
extern int func_ov004_0222c3c4(void *, int);
extern int func_02056f94(void *);
extern char *data_ov004_02258310;
}
extern "C" int func_ov004_0222db58(void)
{
    UnkStruct_0222db58 t;
    char *g = data_ov004_02258310;
    if (g != 0) {
        int a = func_02054ecc(g + 0x348);
        if (a == func_ov004_0222c3c4(g + 0x9ac, 0xc)) {
            if (func_02056f94(data_ov004_02258310 + 0x3e4) != 0) {
                return 1;
            }
        }
    }
    return 0;
}
