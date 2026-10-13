/* func_ov004_0220d7f0 @ 0x0220d7f0, 0x10 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char b[16];
} UnkStruct_0220d7f0;
UnkStruct_0220d7f0 *func_ov004_0220d7f0(char *self, unsigned int i)
{
    if (i < 4) {
        return (UnkStruct_0220d7f0 *) (self + 4) + i;
    }
    return (UnkStruct_0220d7f0 *) (self + 4);
}
