/* func_ov004_022183a4 @ 0x022183a4, 0x14 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    int a, b;
} UnkStruct_022183a4;
char *func_ov004_022183a4(char *self)
{
    UnkStruct_022183a4 *p = (UnkStruct_022183a4 *) self;
    int z = 0;
    UnkStruct_022183a4 *e = (UnkStruct_022183a4 *) (self + 0x10);
    do {
        p->a = z;
        p->b = z;
        p++;
    } while (p != e);
    return self;
}
