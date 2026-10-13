/* func_02052038 @ 0x02052038, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073d90(int);
extern int func_02073918(int, int);
extern void func_02052078(int, int);
extern void func_020520a0(int, int, int);
extern int data_020ccf94;

void func_02052038(int x, int y)
{
    int a;
    a = data_020ccf94;
    if (func_02073d90(a) == 0 || func_02073918(a, 0) != 0) {
        func_02052078(x, y);
    } else {
        func_020520a0(x, y, 0);
    }
}
