/* func_020b3ba0 @ 0x020b3ba0, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021f4bf4[34];
extern void *data_021f4b44;
extern void func_020e9898(int);

void func_020b3ba0(void)
{
    int condition_value0;
    unsigned int i;

    for (i = 0; i < 34; i++) {
        data_021f4bf4[i] = 0;
    }

    if ((condition_value0 = (int) (data_021f4b44))) {
        func_020e9898(condition_value0);
        data_021f4b44 = 0;
    }
}
