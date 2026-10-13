/* func_02081a90 @ 0x02081a90, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02081a90(void *obj, void *src)
{
    *((unsigned short *) ((char *) obj + 0x7c)) |= 4;
    *((unsigned long long *) ((char *) obj + 0x74)) = *((unsigned long long *) src);
}
