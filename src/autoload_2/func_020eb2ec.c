/* func_020eb2ec @ 0x020eb2ec, 0x98 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned short data_021fbefc; // 0x021fbefc
extern int data_0213e6bc;            // 0x0213e6c0
extern int data_021fbf1c;            // 0x021fbf44
extern int data_021fbf2c;            // 0x021fbf0c
int func_020edacc(int arg);

int func_020eb2ec(void)
{
    if (data_021fbefc < 4) {
        return 0;
    }
    if (data_0213e6bc == 0) {
        goto ret0;
    }
    if (data_021fbf1c != 0) {
        func_020edacc(data_021fbf1c);
        func_020edacc(data_021fbf2c);
        data_021fbf1c = 0;
        data_021fbf2c = 0;
    }
    return 1;
ret0:
    return 0;
}
