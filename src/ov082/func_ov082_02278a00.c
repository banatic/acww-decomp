/* func_ov082_02278a00 @ 0x02278a00, 0x28 bytes, Thumb, module ov082
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov082_02279064(void *sub);
extern void func_0202ee5c(void *self);
extern char data_ov082_0227981c;

void *func_ov082_02278a00(void *param)
{
    void *obj = param;
    *(void **) obj = (void *) &data_ov082_0227981c;
    func_ov082_02279064((char *) obj + 0x658);
    func_0202ee5c(obj);
    return obj;
}
