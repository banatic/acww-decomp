/* func_ov002_02207f80 @ 0x02207f80, 0x30 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c9b28;
extern int func_020e9958(int a, int b);
extern int memset(int a, int b, int c);

int func_ov002_02207f80(int param)
{
    int res;
    res = func_020e9958(data_021c9b28, param);
    if (res == 0) {
        return 0;
    }
    memset(res, 0, param);
    return res;
}
