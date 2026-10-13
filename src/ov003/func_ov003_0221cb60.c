/* func_ov003_0221cb60 @ 0x0221cb60, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02056ffc(void *);

void func_ov003_0221cb60(void *self)
{
    func_02056ffc((char *) self + 0x2b4);
    *(int *) (*(int *) ((char *) self + 0x2cc)) = *(int *) ((char *) self + 0x2bc);
}
