/* func_ov004_0223a9b8 @ 0x0223a9b8, 0x26 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char b[0xa8];
} UnkStruct_0223a9b8;
extern int func_ov004_0223a808(char *self);
extern void func_ov004_0223ac34(UnkStruct_0223a9b8 *e);
void func_ov004_0223a9b8(char *self)
{
    if (func_ov004_0223a808(self)) {
        UnkStruct_0223a9b8 *a = (UnkStruct_0223a9b8 *) (self + 4);
        func_ov004_0223ac34(&a[*(short *) self & 1]);
    }
}
