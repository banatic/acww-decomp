/* func_02096c50 @ 0x02096c50, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020ee660(void *);
extern void *data_020da13c;
extern void *data_020e2fe8;

void *func_02096c50(void *obj)
{
    func_020ee660(obj);
    *(volatile void **) obj = &data_020da13c;
    *(volatile void **) obj = &data_020e2fe8;
    return obj;
}
