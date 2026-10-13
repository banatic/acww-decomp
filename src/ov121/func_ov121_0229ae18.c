/* func_ov121_0229ae18 @ 0x0229ae18, 0x50 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

int func_ov121_0229ae68(void *p, unsigned char a, unsigned char b, int c);
int func_ov121_0229af58(void *p, int a);
int func_ov121_0229af40(void *p, int a);

int func_ov121_0229ae18(void *param)
{
    unsigned char g1;
    unsigned char g2;
    int ret;
    int tmp1;
    int tmp2;

    g1 = data_021f6c58;
    g2 = data_021f6c54;
    ret = func_ov121_0229ae68(param, g1, g2, 7);
    if (ret != 0x18) {
        tmp1 = func_ov121_0229af58(param, ret) - g1;
        *((unsigned short *) ((char *) param + 0xa8)) = tmp1;
        tmp2 = func_ov121_0229af40(param, ret) - g2;
        *((unsigned short *) ((char *) param + 0xaa)) = tmp2;
    }
    return ret;
}
