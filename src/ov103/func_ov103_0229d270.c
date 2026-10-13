/* func_ov103_0229d270 @ 0x0229d270, 0x30 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *ptr);
extern void func_ov002_02208098(void *obj, unsigned char value);
extern void func_ov103_0229c994(void *obj);

void func_ov103_0229d270(void *obj)
{
    if (func_0208e484((char *) obj + 0x2274) != 0) {
        func_ov002_02208098(obj, *(unsigned char *) ((char *) obj + 0x2da7));
    }
    func_ov103_0229c994(obj);
}
