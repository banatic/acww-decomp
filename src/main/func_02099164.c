/* func_02099164 @ 0x02099164, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02099164(char *base, unsigned int index, char value)
{
    if (index < 8) {
        (base + index)[0x2454] = value;
    }
}
