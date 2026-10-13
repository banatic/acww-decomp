/* func_020ab9c8 @ 0x020ab9c8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020abc6c(void *obj, int n);
extern void func_0208f0c4(void *obj, int n);

void func_020ab9c8(void *obj)
{
    *(int *) ((char *) obj + 0x13c) = 10;
    func_020abc6c(obj, 9);
    obj = (char *) obj + 0x6c;
    func_0208f0c4(obj, 1);
}
