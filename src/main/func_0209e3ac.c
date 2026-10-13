/* func_0209e3ac @ 0x0209e3ac, 0xc8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

func_0209e3ac(int r0, int r1, int r2)
{
    if (r2 & 0x20) {
        if (*(unsigned char *) (r0 + 5) < *(unsigned char *) (r1 + 5)) {
            return -1;
        }
        if (*(unsigned char *) (r0 + 5) > *(unsigned char *) (r1 + 5)) {
            return 1;
        }
    }
    if (r2 & 0x10) {
        if (*(unsigned char *) (r0 + 4) < *(unsigned char *) (r1 + 4)) {
            return -1;
        }
        if (*(unsigned char *) (r0 + 4) > *(unsigned char *) (r1 + 4)) {
            return 1;
        }
    }
    if (r2 & 0x08) {
        if (*(unsigned char *) (r0 + 3) < *(unsigned char *) (r1 + 3)) {
            return -1;
        }
        if (*(unsigned char *) (r0 + 3) > *(unsigned char *) (r1 + 3)) {
            return 1;
        }
    }
    if (r2 & 0x04) {
        if (*(unsigned char *) (r0 + 2) < *(unsigned char *) (r1 + 2)) {
            return -1;
        }
        if (*(unsigned char *) (r0 + 2) > *(unsigned char *) (r1 + 2)) {
            return 1;
        }
    }
    if (r2 & 0x02) {
        if (*(unsigned char *) (r0 + 1) < *(unsigned char *) (r1 + 1)) {
            return -1;
        }
        if (*(unsigned char *) (r0 + 1) > *(unsigned char *) (r1 + 1)) {
            return 1;
        }
    }
    if (r2 & 0x01) {
        if (*(unsigned char *) (r0) < *(unsigned char *) (r1)) {
            return -1;
        }
        if (*(unsigned char *) (r0) > *(unsigned char *) (r1)) {
            return 1;
        }
    }
    return 0;
}
