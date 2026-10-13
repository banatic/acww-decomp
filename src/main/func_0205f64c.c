/* func_0205f64c @ 0x0205f64c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_02062148(void);
extern unsigned int func_02062230(void);
extern unsigned char data_020cc900[];

int func_0205f64c(void)
{
    unsigned int first, second;
    first = func_02062148();
    second = func_02062230();
    if (first < second) {
        return data_020cc900[first];
    } else {
        return 0x2b;
    }
}
