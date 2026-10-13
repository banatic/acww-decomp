/* func_ov004_0220db5c @ 0x0220db5c, 0xc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b;
} UnkStruct_0220db5c;
UnkStruct_0220db5c *func_ov004_0220db5c(char *self, int i)
{
    return (UnkStruct_0220db5c *) (self + 4) + (i & 3);
}
