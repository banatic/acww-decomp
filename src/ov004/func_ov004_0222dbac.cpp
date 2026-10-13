/* func_ov004_0222dbac @ 0x0222dbac, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0222dbac {
    int a;
    ~UnkStruct_0222dbac() {}
};

extern "C" {
extern int func_02054ecc(void *);
extern int func_ov004_0222c3c4(void *, int);
extern char *data_ov004_02258310;
}
extern "C" int func_ov004_0222dbac(void)
{
    UnkStruct_0222dbac t;
    char *g = data_ov004_02258310;
    if (g != 0) {
        int a = func_02054ecc(g + 0x348);
        if (a == func_ov004_0222c3c4(g + 0x9ac, 0xb)) {
            if (((unsigned) (*(int *) (data_ov004_02258310 + 0x3ec) << 4) >> 16) == 9) {
                return 1;
            }
        }
    }
    return 0;
}
