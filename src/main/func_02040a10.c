/* func_02040a10 @ 0x02040a10, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char MB_GetBeaconRecvStatus(unsigned char *param);
extern unsigned char *func_02040980(unsigned char *param);
extern void func_020409e8(unsigned char *param);

void func_02040a10(unsigned char *param)
{
    unsigned char val;
    unsigned char *p;
    unsigned char b2;
    unsigned char b13;

    val = MB_GetBeaconRecvStatus(param);
    p = func_02040980(param);
    if (p != 0) {
        b2 = p[2];
        b13 = param[0x13];
        if (val != b13 || b2 != param[0x12]) {
            param[0x12] = b2;
            param[0x13] = val;
        }
        func_020409e8(param);
    }
}
