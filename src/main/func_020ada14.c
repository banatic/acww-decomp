/* func_020ada14 @ 0x020ada14, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073d90(int arg);
extern int func_0209782c(void);
extern int data_020ccf94;

int func_020ada14(void)
{
    if (func_02073d90(data_020ccf94) != 0) {
        return 0;
    }
    if (func_0209782c() != 0) {
        return 1;
    }
    return 0;
}
