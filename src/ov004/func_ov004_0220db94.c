/* func_ov004_0220db94 @ 0x0220db94, 0x16 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    int a, b;
} UnkStruct_0220db94;
char *func_ov004_0220db94(char *self)
{
    UnkStruct_0220db94 *p = (UnkStruct_0220db94 *) (self + 4);
    int z = 0;
    UnkStruct_0220db94 *e = (UnkStruct_0220db94 *) (self + 0x24);
    do {
        p->a = z;
        p->b = z;
        p++;
    } while (p != e);
    *(int *) self = z;
    return self;
}
