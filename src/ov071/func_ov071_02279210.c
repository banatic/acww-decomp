/* func_ov071_02279210 @ 0x02279210, 0x80 bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x734];
    int unk_734;
} UnkStruct_02279210;

extern int func_02096190(int);
extern int func_0202ea80(int, int);
extern int func_ov071_02279c18(UnkStruct_02279210 *, int);
extern void func_ov071_02279d04(UnkStruct_02279210 *, int);
extern int func_ov071_02279b2c(UnkStruct_02279210 *, int);

int func_ov071_02279210(UnkStruct_02279210 *p)
{
    p->unk_734 = func_02096190(4);

    if (func_0202ea80(0x28, 0) != 0) {
        if (func_ov071_02279c18(p, 1) != 0) {
            func_ov071_02279d04(p, 3);
            return 1;
        }
    } else {
        if (func_ov071_02279c18(p, 0) != 0 && func_ov071_02279b2c(p, 0x3000) == 0 && func_ov071_02279b2c(p, 0x8000) != 0) {
            func_ov071_02279d04(p, 1);
            return 1;
        }
        func_ov071_02279d04(p, 3);
    }
    return 1;
}
