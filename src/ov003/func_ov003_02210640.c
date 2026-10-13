/* func_ov003_02210640 @ 0x02210640, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020109a0(void *p, int a, int b, int c);

void func_ov003_02210640(void *obj)
{
    func_020109a0(obj, 0x61, 3, 0);
    *(int *) ((char *) obj + 0x7d4) = -1;
}
