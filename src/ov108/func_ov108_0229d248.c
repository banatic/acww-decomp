/* func_ov108_0229d248 @ 0x0229d248, 0x30 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *ptr);
extern void func_ov002_02208098(void *obj, unsigned char byte);
extern void func_ov108_0229c940(void *obj);

void func_ov108_0229d248(void *obj)
{
    if (func_0208e484((char *) obj + 0x2498)) {
        func_ov002_02208098(obj, *((unsigned char *) obj + 0x2b3));
    }
    func_ov108_0229c940(obj);
}
