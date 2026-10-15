/* func_ov052_02261140 @ 0x02261140, 0x18 bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202eb70(void *obj);
extern char data_ov052_02261eb0[];

void *func_ov052_02261140(void *obj)
{
    func_0202eb70(obj);
    *(void **) obj = (void *) data_ov052_02261eb0;
    return obj;
}
