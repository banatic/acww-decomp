/* func_ov094_0229b5c8 @ 0x0229b5c8, 0x20 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229b1e8(int parameter0, int parameter1);
extern unsigned char data_ov094_0229c0fc[];

int func_ov094_0229b5c8(int arg0, int arg1)
{
    int v = func_ov094_0229b1e8(arg0, arg1);
    if (v == -1) {
        return -1;
    }
    return data_ov094_0229c0fc[v];
}
