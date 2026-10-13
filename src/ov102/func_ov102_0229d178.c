/* func_ov102_0229d178 @ 0x0229d178, 0x70 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov102_0229d464(void *, int);
extern int func_ov102_0229d454(void *, int);
extern int func_ov102_0229d400(void *, int);
extern int func_ov102_0229d438(void *, int);
extern int func_ov102_0229d444(void *, int);
extern int func_ov094_0229ab90(const void *, int);
extern int func_02088d94(const void *);
extern char data_ov102_0229eac0[];

int func_ov102_0229d178(void *a, int b)
{
    if (func_ov102_0229d464(a, b) || func_ov102_0229d454(a, b)) {
        return func_ov094_0229ab90((char *) a + 0xcc, func_ov102_0229d400(a, b));
    }
    if (func_ov102_0229d438(a, b)) {
        return 0x70;
    }
    if (func_ov102_0229d444(a, b)) {
        return func_02088d94(data_ov102_0229eac0 + (((b - 0x1e) * 3) << 3)) + 0x68;
    }
    return 0;
}
