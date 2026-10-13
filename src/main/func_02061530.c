/* func_02061530 @ 0x02061530, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209dbbc(void);
extern int func_020e930c(const unsigned int *, int);

extern unsigned char data_021cb5a0[];

int func_02061530(void)
{
    return func_020e930c((const unsigned int *) data_021cb5a0, func_0209dbbc());
}
