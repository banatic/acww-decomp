/* func_ov102_0229d1e8 @ 0x0229d1e8, 0x70 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov102_0229d464(int, int);
extern int func_ov102_0229d454(int, int);
extern int func_ov102_0229d400(int, int);
extern int func_ov102_0229d438(int, int);
extern int func_ov102_0229d444(int, int);
extern int func_ov094_0229aba4(int, int);
extern int func_02088d9c(void *);
extern char data_ov102_0229eac0[][8];

int func_ov102_0229d1e8(int p1, int p2)
{
    if (func_ov102_0229d464(p1, p2) != 0 || func_ov102_0229d454(p1, p2) != 0) {
        return func_ov094_0229aba4(p1 + 0xcc, func_ov102_0229d400(p1, p2));
    } else {
        if (func_ov102_0229d438(p1, p2) != 0) {
            return 0xc4;
        } else {
            if (func_ov102_0229d444(p1, p2) != 0) {
                return func_02088d9c(&data_ov102_0229eac0[(p2 - 0x1e) * 3]) + 0x80;
            } else {
                return 0;
            }
        }
    }
}
