/* func_020b5c68 @ 0x020b5c68, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(int);
extern void func_020ee660(void);
extern int data_020da13c;
extern int data_020e3c94;
extern int data_020e5460;

void *func_020b5c68(void)
{
    void *r4;
    unsigned char r1;

    r4 = func_020edf70(0x50);
    if (r4 != 0) {
        func_020ee660();
        *(int *) r4 = (int) &data_020da13c;
        *(int *) r4 = (int) &data_020e3c94;
        r1 = *(unsigned char *) ((char *) r4 + 0x13);
        r1 |= 1;
        *(unsigned char *) ((char *) r4 + 0x13) = r1;
        r1 = *(unsigned char *) ((char *) r4 + 0x13);
        r1 |= 4;
        *(unsigned char *) ((char *) r4 + 0x13) = r1;
        *(int *) r4 = (int) &data_020e5460;
    }
    return r4;
}
