/* func_020ba2b8 @ 0x020ba2b8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ee62c(void *);
extern void func_020edf54(void *);
extern int data_020e69a4;
extern int data_020da13c;

void *func_020ba2b8(void *obj)
{
    *(volatile int *) obj = (int) &data_020e69a4;
    *(volatile int *) obj = (int) &data_020da13c;
    func_020ee62c(obj);
    func_020edf54(obj);
    return obj;
}
