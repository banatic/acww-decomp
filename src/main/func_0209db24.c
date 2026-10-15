/* func_0209db24 @ 0x0209db24, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(int size);
extern void *func_020ee660(void *);
extern unsigned int data_020da13c;
extern unsigned int data_020e360c;

void *func_0209db24(void)
{
    void *r4;
    void *r0;

    r4 = func_020edf70(0x50);
    if (r4 != 0) {
        func_020ee660(r4);
        *(unsigned int *) r4 = (unsigned int) &data_020da13c;
        *(unsigned int *) r4 = (unsigned int) &data_020e360c;
    }
    return r4;
}
