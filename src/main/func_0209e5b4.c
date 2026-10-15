/* func_0209e5b4 @ 0x0209e5b4, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int RTC_SetDateTime(const void *date, const void *time);

void func_0209e5b4(int *r4, const void *time)
{
    RTC_SetDateTime(r4, time);
    if (r4[0] == 0 && r4[1] == 1 && r4[2] == 1) {
        r4[3] = 6;
    }
}
