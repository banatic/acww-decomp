/* func_020b3ba0 @ 0x020b3ba0, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021f4bf4[34];
extern void *data_021f4b44;
extern void __arm func_020e9898(void);

void func_020b3ba0(void)
{
    unsigned int i;

    for (i = 0; i < 34; i++) {
        data_021f4bf4[i] = 0;
    }

    if (data_021f4b44) {
        func_020e9898();
        data_021f4b44 = 0;
    }
}
