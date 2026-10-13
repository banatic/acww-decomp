/* func_020bbcfc @ 0x020bbcfc, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e98d4(int);

int func_020bbcfc(int *param)
{
    int i;
    int *ptr = param;
    int val = 0x20;

    for (i = 0; i < 3; i++) {
        if (ptr[0] == 0) {
            ptr[0] = func_020e98d4(val);
            if (ptr[0] == 0) {
                return 0;
            }
        }
        ptr++;
    }
    return 1;
}
