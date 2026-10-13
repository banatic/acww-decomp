/* func_ov110_0229cde0 @ 0x0229cde0, 0x2c bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

void func_ov110_0229cde0(unsigned char *param0)
{
    unsigned int val;
    unsigned int val2;

    val2 = *(unsigned int *) (param0 + 0xa0) + data_021f6c58;
    *(unsigned int *) (param0 + 0xa8) = val2;
    val = *(unsigned int *) (param0 + 0xa4) + data_021f6c54;
    *(unsigned int *) (param0 + 0xac) = val;
}
