/* func_ov002_02208918 @ 0x02208918, 0x12 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208918(void *this);

int func_ov002_02208918(void *this)
{
    if ((*(unsigned char *) ((char *) this + 0x10) & 0x40) != 0) {
        return 1;
    }
    return 0;
}
