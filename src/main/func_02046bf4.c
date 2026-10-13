/* func_02046bf4 @ 0x02046bf4, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x20];
    int unk_20;
} GStruct;

extern int func_020423ec(int a0, int a1, int a2, int a3);
extern int func_0204714c(GStruct *p, int a0, int a1, int a2, int a3, int a4);
extern GStruct data_021c779c;

int func_02046bf4(int a0, int a1, int a2, int a3, int a4)
{
    if (data_021c779c.unk_20 != 0) {
        return func_020423ec(a0, a1, a2, a3);
    } else {
        return func_0204714c(&data_021c779c, a0, a1, a2, a3, a4);
    }
}
