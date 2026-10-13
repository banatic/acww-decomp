/* func_ov003_022277fc @ 0x022277fc, 0x10 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

void func_ov003_022277fc(char *o, int v)
{
    *(int *) (o + 0x1f0) = (v << 12) >> 4;
}
