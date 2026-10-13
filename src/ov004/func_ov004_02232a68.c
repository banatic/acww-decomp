/* func_ov004_02232a68 @ 0x02232a68, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int w[12];
} UnkStruct_02232a68;
extern UnkStruct_02232a68 data_021fbe48;
extern void func_020e96c8(UnkStruct_02232a68 *p, int a, int b, int c);
void func_ov004_02232a68(char *self)
{
    func_020e96c8(&data_021fbe48, 0, 0, 0);
    *(UnkStruct_02232a68 *) (self + 0xb4) = data_021fbe48;
}
