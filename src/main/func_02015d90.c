/* func_02015d90 @ 0x02015d90, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02015da0(void *ptr, unsigned char byte);

int func_02015d90(void *ptr)
{
    return func_02015da0(ptr, ((unsigned char *) ptr)[0x54]);
}
