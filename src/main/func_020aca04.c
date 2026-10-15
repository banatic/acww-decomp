/* func_020aca04 @ 0x020aca04, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0208e8d4(void *obj, int arg);
extern unsigned int data_020e4030;

void *func_020aca04(void *param)
{
    func_0208e8d4(param, 1);
    *(unsigned int *) param = (unsigned int) &data_020e4030;
    *((int *) ((char *) param + 0x28)) = 0;
    return param;
}
