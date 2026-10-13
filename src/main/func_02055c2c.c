/* func_02055c2c @ 0x02055c2c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02055c2c {
    int unk_00;
    int unk_04;
};
extern int func_02055bd8(struct UnkStruct_02055c2c *a, int b, int c, int d);
int func_02055c2c(struct UnkStruct_02055c2c *a, int b, int c)
{
    return func_02055bd8(a, c, a->unk_04, b);
}
