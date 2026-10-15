/* func_02009c48 @ 0x02009c48, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02009d20(void *src, void *dst);
extern int func_02009d38(void *src, unsigned short val, int count, void *dst);

void func_02009c48(void *param0, void *param1)
{
    unsigned short local;
    void *ptr;

    func_02009d20((char *) param0 + 0x8f0, &local);
    func_02009d38(param0, local, 6, param1);
}
