/* func_02012550 @ 0x02012550, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208308c(void *p);
extern int func_02082cb8(void *p, void *q);

int func_02012550(void *ptr, void *arg2)
{
    if (!func_0208308c((char *) ptr + 4)) {
        return 0;
    }
    if (!func_02082cb8((char *) ptr + 4, arg2)) {
        return 0;
    }
    *(unsigned short *) ptr = 0xfff1;
    return 1;
}
