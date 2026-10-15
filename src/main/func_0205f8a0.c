/* func_0205f8a0 @ 0x0205f8a0, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205f8b4(unsigned char *);
extern int func_0205f970(void);

int func_0205f8a0(unsigned char *argument0)
{
    int r4;
    int result;

    r4 = func_0205f8b4((unsigned char *) argument0);
    result = func_0205f970();
    return r4 + result;
}
