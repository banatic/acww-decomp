/* obj_020e2fe8: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02096c70 @ 0x02096c70, 0x18 bytes, Thumb
 * func_02096c50 @ 0x02096c50, 0x20 bytes, Thumb
 */

extern void *func_020edf70(unsigned int);
extern void *func_020ee660(void *);
extern void *data_020da13c;
extern void *data_020e2fe8;

void *func_02096c50(void *obj);

void func_02096c70(void)
{
    void *ptr;

    ptr = func_020edf70(0x50);
    if (ptr != 0) {
        func_02096c50(ptr);
    }
}

void *func_02096c50(void *obj)
{
    func_020ee660(obj);
    *(volatile void **) obj = &data_020da13c;
    *(volatile void **) obj = &data_020e2fe8;
    return obj;
}
