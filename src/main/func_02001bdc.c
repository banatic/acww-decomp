/* func_02001bdc @ 0x02001bdc, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02001c08(void *arg);
extern void GXS_SetGraphicsMode(void *arg);

void func_02001bdc(void *arg)
{
    func_02001c08(arg);
    GXS_SetGraphicsMode(arg);
}
