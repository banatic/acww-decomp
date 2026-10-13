/* func_ov105_0229d530 @ 0x0229d530, 0x6c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} UnkData8;

extern int func_ov105_0229d76c(unsigned char *, int);
extern int func_ov105_0229d75c(unsigned char *, int);
extern int func_ov105_0229d718(unsigned char *, int);
extern int func_ov105_0229d73c(unsigned char *, int);
extern int func_ov094_0229b384(unsigned char *, int);
extern int func_02088d9c(UnkData8 *);
extern UnkData8 data_ov105_0229fa80[];

int func_ov105_0229d530(unsigned char *a, int b)
{
    if (func_ov105_0229d76c(a, b) || func_ov105_0229d75c(a, b)) {
        return func_ov094_0229b384(a + 0xd5c, func_ov105_0229d718(a, b));
    }

    if (b == 0x3d) {
        return 0xbc;
    }

    if (func_ov105_0229d73c(a, b)) {
        return func_02088d9c(&data_ov105_0229fa80[(b - 0x3e) * 3]) + 0x80;
    }

    return 0;
}
