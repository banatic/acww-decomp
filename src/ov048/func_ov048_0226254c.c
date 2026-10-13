/* func_ov048_0226254c @ 0x0226254c, 0x3a bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[0x24];
} UnkStruct_0226254c;
extern void func_020984e8(void);
extern void func_02099658(void);
extern UnkStruct_0226254c *func_02077d00(void);
extern int func_02077c3c(UnkStruct_0226254c *);
extern int func_02077e50(int);

int func_ov048_0226254c(void)
{
    UnkStruct_0226254c *base;
    int i;
    func_020984e8();
    func_02099658();
    base = func_02077d00();
    for (i = 0; i < 32; i++) {
        if (func_02077e50(func_02077c3c(&base[i]))) {
            return 1;
        }
    }
    return 0;
}
