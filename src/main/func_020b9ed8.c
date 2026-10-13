/* func_020b9ed8 @ 0x020b9ed8, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b9ec4(void *arg0);

void func_020b9ed8(void *arg0)
{
    void *r4;

    r4 = arg0;
    func_020b9ec4(r4);
    *(unsigned char *) ((unsigned int) r4 + 0xd) = 1;
}
