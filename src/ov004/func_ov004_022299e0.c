/* func_ov004_022299e0 @ 0x022299e0, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    int a, b, c;
} UnkStruct_022299e0;
void func_ov004_022299e0(char *self)
{
    UnkStruct_022299e0 *q = (UnkStruct_022299e0 *) (self + 0x5c);
    int *p = (int *) (self + 0x7d4);
    *(int *) (self + 0x5c) = p[0];
    q->c = p[1];
}
