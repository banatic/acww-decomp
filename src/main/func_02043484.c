/* func_02043484 @ 0x02043484, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y;
} Pair;

extern void *func_0204f5e0(int a, int hi2, int hi3, int lo2, int lo3, int z);
extern int func_020317c4(int a, int b, int c, int d, int e);
extern int func_0204ed80(int a, int b, int c);

void *func_02043484(int p0, int p1, int p2, int p3, Pair *p4)
{
    int hi2 = p2 >> 4;
    int hi3 = p3 >> 4;
    int lo3 = p3 - (hi3 << 4);
    int lo2 = p2 - (hi2 << 4);
    void *r5;

    r5 = func_0204f5e0(p1, hi2, hi3, lo2, lo3, 0);
    if (r5 == 0) {
        goto exit;
    }
    if (*(unsigned short *) r5 != 0xFFF1) {
        r5 = 0;
        goto exit;
    }

    switch ((unsigned int) (p0 - 16)) {
        case 0:
        case 1:
        case 2:
            if (func_020317c4(p4->x, p4->y, p2, p3, 0) == 0) {
                r5 = 0;
            }
            break;
        case 8: {
            int res = func_0204ed80(p1, p2, p3);
            if (res != 0 && res != 1) {
                r5 = 0;
            }
            break;
        }
        case 10:
            if (func_020317c4(p4->x, p4->y, p2, p3, 1) == 0) {
                r5 = 0;
            }
            break;
        default:
            break;
    }

exit:
    return r5;
}
