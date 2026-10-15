/* func_02097c90 @ 0x02097c90, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(unsigned int size);
extern void *func_020ee660(void *obj);
extern unsigned int data_020da13c;
extern unsigned int data_020e30b8;

void *func_02097c90(void)
{
    void *p = func_020edf70(0x54);
    if (p) {
        func_020ee660(p);
        ((volatile unsigned int *) p)[0] = (unsigned int) &data_020da13c;
        ((volatile unsigned int *) p)[0] = (unsigned int) &data_020e30b8;
    }
    return p;
}
