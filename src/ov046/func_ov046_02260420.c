/* func_ov046_02260420 @ 0x02260420, 0x28 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov046_022612ec(void *ptr);
extern void func_0202ee5c(void *ptr);
extern int data_ov046_022620e0;

int *func_ov046_02260420(int *obj)
{
    obj[0] = (int) &data_ov046_022620e0;
    func_ov046_022612ec((char *) obj + 0x658);
    func_0202ee5c(obj);
    return obj;
}
