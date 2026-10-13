/* func_0208c020 @ 0x0208c020, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208be3c(void *param);
extern void func_0208c688(void *param);

void func_0208c020(void *param)
{
    unsigned char *p = (unsigned char *) param;
    p[0x26] = 0;
    p[0x24] = 0;
    p[0x25] = 0;
    func_0208be3c(param);
    func_0208c688((void *) ((unsigned char *) param + 0x28));
}
