/* func_0205cf84 @ 0x0205cf84, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205c814(void);
extern void func_0205cda0(void *param);
extern void func_020e9abc(void);

extern unsigned char data_021c9af8[];
extern unsigned char data_021c9b58[];

void func_0205cf84(void)
{
    void *ptr;
    func_0205c814();
    func_0205cda0((void *) data_021c9b58);
    ptr = *(void **) data_021c9af8;
    if (ptr != 0) {
        func_020e9abc();
    }
}
