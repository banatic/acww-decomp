/* func_ov004_0222b2d8 @ 0x0222b2d8, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    int a, b, c;
} UnkStruct_0222b2d8;
void func_ov004_0222b2d8(char *self, int stateId)
{
    int *p = (int *) (self + 0x7d4);
    UnkStruct_0222b2d8 *q = (UnkStruct_0222b2d8 *) (self + 0x5c);
    *(int *) (self + 0x5c) = p[0];
    q->c = p[1];
}
