/* func_02086ed4 @ 0x02086ed4, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char flag : 1;
} FlagStruct;

int func_02086ed4(const FlagStruct *p)
{
    if (p->flag) {
        return 1;
    } else {
        return 0;
    }
}
