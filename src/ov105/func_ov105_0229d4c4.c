/* func_ov105_0229d4c4 @ 0x0229d4c4, 0x6c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov105_0229d76c(void *, int);
extern int func_ov105_0229d75c(void *, int);
extern int func_ov105_0229d718(void *, int);
extern int func_ov105_0229d73c(void *, int);
extern int func_ov094_0229b328(void *, int);
extern int func_02088d94(void *);
extern int data_ov105_0229fa80[][2];

int func_ov105_0229d4c4(char *p1, int p2)
{
    if (func_ov105_0229d76c(p1, p2) != 0 || func_ov105_0229d75c(p1, p2) != 0) {
        return func_ov094_0229b328(p1 + 0xd5c, func_ov105_0229d718(p1, p2)) - 0x10;
    }
    if (p2 == 0x3d) {
        return 0xb6;
    }
    if (func_ov105_0229d73c(p1, p2) != 0) {
        return func_02088d94(&data_ov105_0229fa80[(p2 - 0x3e) * 3]) + 0x58;
    }
    return 0;
}
