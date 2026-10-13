/* func_0204b4fc @ 0x0204b4fc, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204b48c(void *, int, int);

int func_0204b4fc(void *param)
{
    if (func_0204b48c(param, 0x12, 0x19) != 0 || *(unsigned short *) param == 0x1c) {
        return 1;
    }
    return 0;
}
