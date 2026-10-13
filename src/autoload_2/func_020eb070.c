/* func_020eb070 @ 0x020eb070, 0x98 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned short data_021fbefc; // 0x021fbefc
extern int data_0213e6c0;            // 0x0213e6c0
extern int data_021fbf44;            // 0x021fbf44
extern int data_021fbf0c;            // 0x021fbf0c
void UTi_PutString(int arg);

int func_020eb070(void)
{
    if (data_021fbefc < 4) {
        return 0;
    }
    if (data_0213e6c0 == 0) {
        goto ret0;
    }
    if (data_021fbf44 != 0) {
        UTi_PutString(data_021fbf44);
        UTi_PutString(data_021fbf0c);
        data_021fbf44 = 0;
        data_021fbf0c = 0;
    }
    return 1;
ret0:
    return 0;
}
