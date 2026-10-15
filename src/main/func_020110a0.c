/* func_020110a0 @ 0x020110a0, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    short first;
    short second;
} Pair;
void func_020110a0(void *s, short *src)
{
    Pair *current = (Pair *) ((char *) s + 0x8c);
    current->second = *src;
    *(short *) ((char *) s + 0x94) = current->second;
}
