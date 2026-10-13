/* func_020874c4 @ 0x020874c4, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(void *p);
extern int MB_GetBeaconRecvStatus(void);
int func_020874c4(unsigned char *arg)
{
    int flag = 0;
    int local[3];
    int status;
    int index;
    unsigned char c;
    unsigned short h;
    c = 0;
    local[c] = flag;
    local[1] = flag;
    func_0209e474(local);
    if (((unsigned char *) local)[2] >= 12) {
        flag++;
    }
    status = MB_GetBeaconRecvStatus();
    index = (status << 1) + flag;
    c = (arg + index)[10];
    if (c != 0) {
        return c;
    }
    h = *((unsigned short *) (arg + 8));
    if (h == 0) {
        return c;
    }
    return h;
}
