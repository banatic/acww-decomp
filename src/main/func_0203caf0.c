/* func_0203caf0 @ 0x0203caf0, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020edf70(int);
extern int func_020ee660(void);
extern int MTX_Identity43_(int);

extern int data_020da13c;
extern int data_020e58cc;
extern int data_020da87c;

int func_0203caf0(void)
{
    int *r4;
    r4 = (int *) func_020edf70(0x234);
    if (r4 != 0) {
        func_020ee660();
        *r4 = (int) &data_020da13c;
        *r4 = (int) &data_020e58cc;
        MTX_Identity43_((int) (r4 + 0x14));
        *r4 = (int) &data_020da87c;
    }
    return (int) r4;
}
