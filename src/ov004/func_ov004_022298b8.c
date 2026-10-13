/* func_ov004_022298b8 @ 0x022298b8, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a, b, c;
} UnkStruct_022298b8;
void func_ov004_022298b8(char *self)
{
    UnkStruct_022298b8 *q = (UnkStruct_022298b8 *) (self + 0x5c);
    int *p = (int *) (self + 0x7d4);
    *(int *) (self + 0x5c) = p[0];
    q->c = p[1];
    *(int *) (self + 0x68) = *(int *) (self + 0x5c);
    *(int *) (self + 0x6c) = q->b;
    *(int *) (self + 0x70) = q->c;
}
