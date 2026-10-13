/* func_ov096_0229ea88 @ 0x0229ea88, 0x2c bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58; // 0x021f6c58
extern unsigned char data_021f6c54; // 0x021f6c54

void func_ov096_0229ea88(void *p)
{
    int t;
    t = *(int *) ((char *) p + 0x9c);
    t += data_021f6c58;
    *(int *) ((char *) p + 0xa4) = t;

    t = *(int *) ((char *) p + 0xa0);
    t += data_021f6c54;
    *(int *) ((char *) p + 0xa8) = t;
}
