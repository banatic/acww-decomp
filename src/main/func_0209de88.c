/* func_0209de88 @ 0x0209de88, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209df64(void *);
extern int func_0209dcdc(void *, void *);
extern int MB_GetBeaconRecvStatus(void);
int func_0209de88(char p1, char p2, char p3)
{
    char arr[4];
    int buf[2];
    int x;
    int ax;
    int rem;
    arr[2] = p1;
    arr[1] = p2;
    arr[0] = p3;
    func_0209df64(buf);
    x = func_0209dcdc(arr, buf);
    ax = (x < 0) ? (-x) : (x);
    rem = ax % 7;
    if (x < 0) {
        rem = 7 - rem;
    }
    x = MB_GetBeaconRecvStatus();
    return (x + rem) % 7;
}
