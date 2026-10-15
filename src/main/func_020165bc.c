/* func_020165bc @ 0x020165bc, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02016618(int param);
extern int func_02082fec(int param, int arg2);
extern int func_0205cb94(void *object);
extern int NNS_G3dGetJntAnmSet(int arg);
extern int func_02107b44(int arg1, int arg2);

int func_020165bc(int param)
{
    int forwarded_value;

    int result = 0;
    if (func_02016618(param) != 0) {
        if ((forwarded_value = (int) func_02082fec(param, 2)) != 0) {
            result = func_02107b44(NNS_G3dGetJntAnmSet(func_0205cb94((void *) forwarded_value)), 0);
        }
    }
    return result;
}
