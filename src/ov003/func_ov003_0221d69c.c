/* func_ov003_0221d69c @ 0x0221d69c, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_0223c928[];

int func_ov003_0221d69c(void *obj)
{
    int in_range = 0;
    unsigned int val;
    int idx;

    val = *(unsigned short *) ((char *) obj + 0x136);
    if ((val >= 0x5001) && (val <= 0x5008)) {
        in_range = 1;
    }
    if (in_range) {
        idx = val - 0x5001;
    } else {
        idx = -1;
    }
    data_ov003_0223c928[idx] = 0;
    return 1;
}
