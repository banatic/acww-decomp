/* func_ov003_0221fea4 @ 0x0221fea4, 0x10 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

void *func_ov003_0221fea4(void **p, unsigned int index)
{
    if (index < 5) {
        return *(p + index + 1);
    }
    return 0;
}
