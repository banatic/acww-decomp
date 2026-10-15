/* func_ov048_02263284 @ 0x02263284, 0x6c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *p);
extern int func_0203ad88(void);
extern int func_ov004_0222d4f4(void);
extern int func_020e8840(void *p);
extern int func_0203e020(void *p);

int func_ov048_02263284(void *p)
{
    unsigned char state = *(unsigned char *) ((char *) p + 0x0e71);
    switch (state) {
        case 0:
            if (func_02014868((void *) ((char *) p + 0x0618)) == 0) {
                *((unsigned char *) ((char *) p + 0x0e71)) = 1;
            }
            break;
        case 1:
            if (func_0203ad88() == 0) {
                func_ov004_0222d4f4();
                *((unsigned short *) ((char *) p + 0x0e6e)) = 0x3c;
                *((unsigned char *) ((char *) p + 0x0e71)) = 2;
            }
            break;
        case 2:
            if (func_020e8840((void *) ((char *) p + 0x0e6e)) == 0) {
                func_0203e020(p);
            }
            break;
    }
    return 1;
}
