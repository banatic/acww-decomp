/* func_02086ee8 @ 0x02086ee8, 0x250 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char a : 1;
    unsigned char b : 3;
    unsigned char c : 3;
    unsigned char d : 1;
} UnkStruct_02086ee8;

extern int func_020644cc(int n);
extern int MB_GetBeaconRecvStatus(void);
extern int func_020e8b0c(int v, int lo, int hi);
extern int func_020af028(void *p);
extern char data_021f395c[];

void func_02086ee8(UnkStruct_02086ee8 *s)
{
    int x, y, z;
    int m;

    s->a = (unsigned char) func_020644cc(2);
    s->d = 1;
    x = func_020644cc(0x64);
    y = func_020644cc(0x64);
    z = func_020644cc(0x64);
    m = MB_GetBeaconRecvStatus();
    switch (m) {
        case 6:
            if (func_020e8b0c(x, 0, 0x4a) != 0) {
                s->b = 0;
            } else if (func_020e8b0c(x, 0x4b, 0x54) != 0) {
                s->b = 1;
            } else {
                s->b = 2;
            }
            if (func_020e8b0c(y, 0, 0x4a) != 0) {
                s->c = 0;
            } else if (func_020e8b0c(y, 0x4b, 0x54) != 0) {
                s->c = 1;
            } else {
                s->c = 2;
            }
            break;
        case 0:
            if (func_020e8b0c(x, 0, 0x31) != 0) {
                s->b = 0;
            } else if (func_020e8b0c(x, 0x32, 0x3b) != 0) {
                s->b = 1;
            } else if (func_020e8b0c(x, 0x3c, 0x46) != 0) {
                s->b = 2;
            } else {
                s->b = 4;
            }
            if (func_020e8b0c(y, 0, 0x4a) != 0) {
                s->c = 0;
            } else if (func_020e8b0c(y, 0x4b, 0x54) != 0) {
                s->c = 1;
            } else if (func_020e8b0c(y, 0x55, 0x5e) != 0) {
                s->c = 2;
            } else {
                s->c = 3;
            }
            break;
        default:
            if (func_020e8b0c(x, 0, 0x4a) != 0) {
                s->b = 0;
            } else if (func_020e8b0c(x, 0x4b, 0x55) != 0) {
                s->b = 1;
            } else {
                s->b = 2;
            }
            if (func_020e8b0c(y, 0, 0x4a) != 0) {
                s->c = 0;
            } else if (func_020e8b0c(y, 0x4b, 0x55) != 0) {
                s->c = 1;
            } else {
                s->c = 2;
            }
            if (func_020e8b0c(z, 0, 0x1d) != 0 && func_020af028(data_021f395c) == 3) {
                s->d = 1;
            } else {
                s->d = 0;
            }
            break;
    }
    if (s->b == s->c) {
        s->c = 0;
    }
}
