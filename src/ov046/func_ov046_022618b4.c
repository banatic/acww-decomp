/* func_ov046_022618b4 @ 0x022618b4, 0x3c bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);

extern unsigned short data_020c80f8;

int func_ov046_022618b4(void *self)
{
    int arg5;
    int arg6;
    int arg7;
    int arg8;
    int arg9;
    int arg10;
    int arg11;

    arg5 = 0;
    arg6 = 0;
    arg7 = *(signed short *) ((char *) self + 0x73a);
    arg8 = 0;
    arg9 = 0;
    arg10 = data_020c80f8;
    arg11 = 0;

    func_02019d0c((char *) self + 0x564, 3, 1, 0, arg5, arg6, arg7, arg8, arg9, arg10, arg11);
    return 1;
}
