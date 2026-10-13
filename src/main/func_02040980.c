/* func_02040980 @ 0x02040980, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021dc7a8[];
extern int MB_GetBeaconRecvStatus(void);
extern void func_0209e474(void *ptr);
extern int func_020409c8(const void *ptr, int count);

int func_02040980(void)
{
    char *base = (char *) data_021dc7a8;
    int result = 0;
    int status = MB_GetBeaconRecvStatus();

    if (status != 0) {
        struct {
            int a;
            int b;
        } local;
        local.a = 0;
        local.b = 0;

        func_0209e474(&local);
        if (((unsigned char *) &local)[2] < 6) {
            status--;
        }
        result = func_020409c8(base + 0x17218, status);
    }

    return result;
}
