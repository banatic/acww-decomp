/* func_0204cf64 @ 0x0204cf64, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021fbe94;
extern void *data_021c80bc;

void func_0204d544(int a, int b);
void func_0204ecd4(void *a, int b);
void func_020e993c(int a, void *b);

int func_0204cf64(int param)
{
    int v = data_021fbe94;
    if (data_021c80bc) {
        func_0204d544(param, v);
        func_0204ecd4(data_021c80bc, v);
        func_020e993c(v, data_021c80bc);
        data_021c80bc = 0;
    }
    return 1;
}
