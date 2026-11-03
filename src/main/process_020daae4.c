/* process_020daae4: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203de9c @ 0x0203de9c, 0x28 bytes, Thumb
 * func_0203de7c @ 0x0203de7c, 0x20 bytes, Thumb
 */

extern void func_020ee62c(void *); // 0x020ee62c
extern void func_020edf54(void *); // 0x020edf54
extern unsigned char data_020da13c[];
extern unsigned char data_020daae4[];

void *func_0203de9c(void *obj)
{
    *(volatile void **) obj = (void *) data_020daae4;
    *(volatile void **) obj = (void *) data_020da13c;
    func_020ee62c(obj);
    func_020edf54(obj);
    return obj;
}

void *func_0203de7c(void *ptr)
{
    *(volatile unsigned int *) ptr = (unsigned int) data_020daae4;
    *(volatile unsigned int *) ptr = (unsigned int) data_020da13c;
    func_020ee62c(ptr);
    return ptr;
}
