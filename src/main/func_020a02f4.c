/* func_020a02f4 @ 0x020a02f4, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_02073dd4(void *p, int i);
extern int func_02073918(void *p, int i);

int func_020a02f4(unsigned char *param)
{
    int result = 1;
    int i = 3;
    void *st = data_020ccf94;

    for (; i >= 0; i--) {
        if (func_02073dd4(st, i) != 0 && func_02073918(st, i) == 0 && *(param + i + 0xf8) == 0) {
            result = 0;
            break;
        }
    }
    return result;
}
