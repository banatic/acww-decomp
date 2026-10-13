/* func_0204087c @ 0x0204087c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(unsigned int size);
extern void func_020ee660(void);

extern unsigned int data_020da13c;
extern unsigned int data_020dabc0;

void *func_0204087c(void)
{
    void *r4;

    r4 = func_020edf70(0x50);
    if (r4 != 0) {
        func_020ee660();
        *(unsigned int *) r4 = (unsigned int) &data_020da13c;
        *(unsigned int *) r4 = (unsigned int) &data_020dabc0;
    }
    return r4;
}
