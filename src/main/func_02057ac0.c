/* func_02057ac0 @ 0x02057ac0, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_02057b08(unsigned int arg);

unsigned int func_02057ac0(unsigned int arg)
{
    unsigned int result;

    result = func_02057b08(arg);
    switch ((arg & 0x1c000000) >> 26) {
        case 2:
            result >>= 2;
            break;
        case 3:
            result >>= 1;
            break;
        case 5:
            result >>= 2;
            break;
        case 7:
            result <<= 1;
            break;
        default:
            break;
    }
    return result;
}
