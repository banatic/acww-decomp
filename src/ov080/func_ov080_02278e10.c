/* func_ov080_02278e10 @ 0x02278e10, 0x20 bytes, Thumb, module ov080
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb20(void *a, void *b);
extern void func_020edb3c(void *a);

extern unsigned char data_ov080_0227925c[];

void *func_ov080_02278e10(void *obj)
{
    void *data = (void *) data_ov080_0227925c;
    *(void **) obj = data;
    func_0202eb20(obj, data);
    func_020edb3c(obj);
    return obj;
}
