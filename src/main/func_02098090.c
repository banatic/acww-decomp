/* func_02098090 @ 0x02098090, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char *func_02098090(char *base, int idx);

char *func_02098090(char *base, int idx)
{
    if (idx >= 0 && idx < 10) {
        return base + (idx << 8);
    }
    return 0;
}
