/* func_020381d8 @ 0x020381d8, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8bb8(void *, void *);
extern void func_020381a4(void *);

extern unsigned char data_021c59d0[];
extern unsigned char data_021c5a24[];

void func_020381d8(void *param0)
{
    void *r4;
    r4 = param0;
    func_020a8bb8((void *) ((unsigned int) r4 + 0xe8), (void *) data_021c5a24);
    func_020a8bb8((void *) ((unsigned int) r4 + 0x1fc), (void *) data_021c59d0);
    func_020381a4(r4);
}
