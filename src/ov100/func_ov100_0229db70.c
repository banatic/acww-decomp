/* func_ov100_0229db70 @ 0x0229db70, 0x30 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov100_0229ce24(void *);

void func_ov100_0229db70(void *obj)
{
    if (func_0208e484((char *) obj + 0x2274)) {
        func_ov002_02208098((void *) (obj), *(unsigned char *) ((char *) obj + 0x2924));
    }
    func_ov100_0229ce24(obj);
}
