/* func_0205f698 @ 0x0205f698, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020cc8c0[];
extern unsigned int func_02062148(unsigned short *);
extern unsigned int func_02062230(void);

unsigned char func_0205f698(unsigned short *argument0)
{
    unsigned int a, b;

    a = func_02062148((unsigned short *) argument0);
    b = func_02062230();
    if (a < b) {
        return data_020cc8c0[a];
    } else {
        return 0x32;
    }
}
