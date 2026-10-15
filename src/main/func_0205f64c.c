/* func_0205f64c @ 0x0205f64c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_02062148(unsigned short *);
extern unsigned int func_02062230(void);
extern unsigned char data_020cc900[];

int func_0205f64c(unsigned short *argument0)
{
    unsigned int first, second;
    first = func_02062148((unsigned short *) argument0);
    second = func_02062230();
    if (first < second) {
        return data_020cc900[first];
    } else {
        return 0x2b;
    }
}
