/* func_020ed5f8 @ 0x020ed5f8, 0x60 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned long long OS_GetTick(void);
extern unsigned int data_021fbf34;

void func_020ed5f8(int a, int b)
{
    if (a != 0) {
        return;
    }
    if (b != 0) {
        return;
    }
    data_021fbf34 = (unsigned int) ((OS_GetTick() << 6) / 0x82ea);
}
