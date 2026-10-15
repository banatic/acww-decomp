/* func_ov104_0229e070 @ 0x0229e070, 0x2c bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov104_0229d528(void *);

void func_ov104_0229e070(void *param)
{
    if (func_0208e484((char *) param + 0x24a0)) {
        func_ov002_02208098((void *) (param), *(unsigned char *) ((char *) param + 0xbb));
    }
    func_ov104_0229d528(param);
}
