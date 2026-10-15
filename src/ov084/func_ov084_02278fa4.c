/* func_ov084_02278fa4 @ 0x02278fa4, 0x18 bytes, Thumb, module ov084
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202eb20(void *);
extern char data_ov084_0227941c;

void *func_ov084_02278fa4(void *obj)
{
    *(void **) obj = (void *) &data_ov084_0227941c;
    func_0202eb20(obj);
    return obj;
}
