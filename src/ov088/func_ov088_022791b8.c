/* func_ov088_022791b8 @ 0x022791b8, 0x50 bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern void func_02019d0c(void *base, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern void func_02013c04(void *);

int func_ov088_022791b8(void *param)
{
    func_02019d0c((char *) param + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    *((char *) param + 0x738) = 0;
    func_02013c04((char *) param + 0x558);
    return 1;
}
