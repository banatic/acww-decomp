/* cafe_props_2: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222dbac @ 0x0222dbac, 0x54 bytes, Thumb
 * func_ov004_0222db58 @ 0x0222db58, 0x54 bytes, Thumb
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

struct UnkStruct_0222db58 {
    int a;
    ~UnkStruct_0222db58() {}
};

extern "C" {
extern int func_02056f94(void *);
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
