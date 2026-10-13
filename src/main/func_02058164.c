/* func_02058164 @ 0x02058164, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02059674(void *param1, int param2);

void func_02058164(void *param1)
{
    void *r4;
    r4 = param1;
    func_02059674(r4, 1);
    r4 = (char *) r4 + 0xd6;
    *(unsigned short *) r4 = 0;
}
