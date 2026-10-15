/* func_020bef88 @ 0x020bef88, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void DC_FlushRange(void *startAddr, unsigned int nBytes);

void func_020bef88(void *object)
{
    DC_FlushRange((unsigned char *) object + 0x448, 0xc00);
}
