/* func_0206aa4c @ 0x0206aa4c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x24];
    unsigned int value;
} UnkStruct_0206aa4c;

extern void func_0200467c(int cmd);
extern void func_02067f28(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

void func_0206aa4c(UnkStruct_0206aa4c *param)
{
    func_0200467c(8);
    func_02067f28(param->value, 0x11000, 0xa66, 0xccc, 0x1000);
}
