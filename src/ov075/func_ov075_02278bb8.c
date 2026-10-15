/* func_ov075_02278bb8 @ 0x02278bb8, 0x18 bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202eb70(void *);
extern char data_ov075_0227996c;

void *func_ov075_02278bb8(void *p)
{
    func_0202eb70(p);
    *(void **) p = &data_ov075_0227996c;
    return p;
}
