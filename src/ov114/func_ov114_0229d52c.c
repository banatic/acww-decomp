/* func_ov114_0229d52c @ 0x0229d52c, 0x20 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208ea70(int *object, int a, int b);

void func_ov114_0229d52c(void *self, int param)
{
    int *field = (int *) ((char *) self + 0x121c);
    func_0208ea70(field, (int) (*(unsigned int *) ((char *) self + 0x1270) - 0x4eU), (int) ((unsigned int) param + 0x4aU));
}
