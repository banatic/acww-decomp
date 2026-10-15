/* func_020b3408 @ 0x020b3408, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02064328(void *p1, void *p2, int p3);

extern unsigned char data_020e50f4[];
extern unsigned char data_021f4b58[];

void *func_020b3408(int unused, int param)
{
    func_02064328((void *) data_021f4b58, (void *) data_020e50f4, param);
    return (void *) data_021f4b58;
}
