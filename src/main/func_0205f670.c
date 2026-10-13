/* func_0205f670 @ 0x0205f670, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_02062148(void);
extern unsigned int func_02062230(void);
extern unsigned short data_020cc940[];

unsigned int func_0205f670(void)
{
    unsigned int a;
    unsigned int b;
    a = func_02062148();
    b = func_02062230();
    if (a < b) {
        return data_020cc940[a];
    } else {
        return 0x144;
    }
}
