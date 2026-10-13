/* func_ov094_0229b5c8 @ 0x0229b5c8, 0x20 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229b1e8(void);
extern unsigned char data_ov094_0229c0fc[];

int func_ov094_0229b5c8(void)
{
    int v = func_ov094_0229b1e8();
    if (v == -1) {
        return -1;
    }
    return data_ov094_0229c0fc[v];
}
