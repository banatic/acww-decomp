/* func_020ee45c @ 0x020ee45c, 0x14 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x10];
    int val;
} UnkStruct_020ee45c;

typedef struct {
    char pad_00[0x14];
    UnkStruct_020ee45c *ptr;
} UnkStruct_020ee45c_2;

int func_020ee45c(UnkStruct_020ee45c_2 *arg)
{
    return arg->ptr ? arg->ptr->val : 0;
}
