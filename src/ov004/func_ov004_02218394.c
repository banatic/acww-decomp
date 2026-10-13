/* func_ov004_02218394 @ 0x02218394, 0xa bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b;
} UnkStruct_02218394;
UnkStruct_02218394 *func_ov004_02218394(UnkStruct_02218394 *p, int i)
{
    return &p[i & 1];
}
