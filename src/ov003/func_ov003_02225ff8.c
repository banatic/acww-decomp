/* func_ov003_02225ff8 @ 0x02225ff8, 0x50 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov003_0223cf70;
extern void *data_ov003_02239dc8[];
extern void *data_ov003_0223cf78;
int func_020555c8(void *a, void *b, void *c);

int func_ov003_02225ff8(void)
{
    int i;
    for (i = 0; i < 2; i++) {
        if (func_020555c8((char *) data_ov003_0223cf70 + 0x49a8 + 0x9c * i, data_ov003_02239dc8[i], data_ov003_0223cf78) ==
            0) {
            return 0;
        }
    }
    return 1;
}
