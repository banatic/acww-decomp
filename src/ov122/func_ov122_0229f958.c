/* func_ov122_0229f958 @ 0x0229f958, 0x28 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov122_0229efe8(void *p, int n);
int func_ov122_0229f958(unsigned char *p)
{
    if ((func_ov122_0229efe8(p, 8) == 0) || (p[0xad] == p[0xae])) {
        return 0;
    }
    return 1;
}
