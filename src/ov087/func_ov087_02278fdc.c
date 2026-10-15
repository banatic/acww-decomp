/* func_ov087_02278fdc @ 0x02278fdc, 0x18 bytes, Thumb, module ov087
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov087_0227945c;
extern void *func_0202eb20(void *obj);

void *func_ov087_02278fdc(void *obj)
{
    *(void **) obj = (void *) &data_ov087_0227945c;
    func_0202eb20(obj);
    return obj;
}
