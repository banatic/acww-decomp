/* func_0203ed2c @ 0x0203ed2c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(unsigned int size);
extern void *func_020ee660(void *ptr);

extern unsigned char data_020da13c[];
extern unsigned char data_020daae4[];

void *func_0203ed2c(void)
{
    void *ptr = func_020edf70(0x50);
    if (ptr) {
        func_020ee660(ptr);
        *(void **) ptr = (void *) data_020da13c;
        *(void **) ptr = (void *) data_020daae4;
    }
    return ptr;
}
