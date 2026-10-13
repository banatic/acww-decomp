/* func_ov050_022628c8 @ 0x022628c8, 0x48 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_02099fe8(void);
extern void func_0206844c(unsigned int, unsigned int, int);

extern unsigned char data_021f43e8[];

void func_ov050_022628c8(unsigned int *param)
{
    if (((unsigned char *) *((unsigned int *) ((char *) param + 0xb4)))[0x73e] == 0 && func_02099fe8() != -1) {
        *(unsigned int *) ((char *) param + 0xd0) = 0x22;
        return;
    }
    ((unsigned char *) *((unsigned int *) ((char *) param + 0xb4)))[0x73e] = 1;
    func_0206844c(*(unsigned int *) ((char *) param + 0x40), (unsigned int) data_021f43e8, 0);
}
