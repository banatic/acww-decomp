/* func_020a5210 @ 0x020a5210, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(unsigned int size);
extern void func_020ee660(void *obj);
extern int func_020a2584(void *ptr);

extern unsigned char data_020da13c[];
extern unsigned char data_020e3ae8[];

void *func_020a5210(void)
{
    void *p = func_020edf70(0x110);
    if (p) {
        func_020ee660(p);
        *(volatile unsigned int *) p = (unsigned int) (unsigned int) data_020da13c;
        *(volatile unsigned int *) p = (unsigned int) (unsigned int) data_020e3ae8;
        func_020a2584((char *) p + 0x54);
        *(unsigned int *) ((char *) p + 0xdc) = 0;
        *(unsigned int *) ((char *) p + 0xe0) = 0;
    }
    return p;
}
