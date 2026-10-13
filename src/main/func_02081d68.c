/* func_02081d68 @ 0x02081d68, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02081cec(void *obj, signed char val);

int func_02081d68(void *obj)
{
    unsigned short raw = *(unsigned short *) ((char *) obj + 0x7c);
    int n = ((unsigned int) raw << 21) >> 29;
    if (n > 4) {
        n = 4;
    }
    n++;
    return func_02081cec(obj, (signed char) n);
}
