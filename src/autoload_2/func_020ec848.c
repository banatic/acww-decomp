/* func_020ec848 @ 0x020ec848, 0xd8 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int func_ov066_022672b8(int a, int b, int c);
extern unsigned long long OS_GetTick(void);
extern int func_ov066_0226760c(void);
extern void func_ov066_0226b90c(void);
extern int func_ov066_02267404(void);

extern unsigned int data_0213e6b8;
extern unsigned char data_021fbef8;

int func_020ec848(void)
{
    unsigned int start;
    unsigned int over;

    func_ov066_022672b8(0, 0, 0);
    start = (unsigned int) ((OS_GetTick() << 6) / 0x82ea);
    while (func_ov066_0226760c() != 2) {
        over = (unsigned int) (((unsigned long long) ((OS_GetTick() << 6) / 0x82ea) - start) > data_0213e6b8);
        if (over != 0) {
            return 0;
        }
    }
    func_ov066_0226b90c();
    if (func_ov066_02267404() == 0) {
        return 0;
    }
    data_021fbef8 = 6;
    return 1;
}
