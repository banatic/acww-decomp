/* func_020a9034 @ 0x020a9034, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c8194;
extern int data_021c81bc;
extern int func_020e9948(int, int);
extern int func_020a8f50(int, int, int, int);
extern void NNS_FndAppendListObject(int *, int);

int func_020a9034(int a, int b, int c)
{
    int flag = 0;
    int ret;
    int p;

    p = func_020e9948(data_021c8194, 0x84);
    ret = flag;
    if (p != 0) {
        ret = p ? func_020a8f50(p, a, b, c) : p;
        flag = 1;
    }
    if (flag != 0) {
        NNS_FndAppendListObject(&data_021c81bc, ret);
    }
    return ret;
}
