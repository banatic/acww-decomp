/* func_020514dc @ 0x020514dc, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020dcf88;
extern int data_020dcf90;
extern int data_020dcf98;
extern int data_020dcfa0;
extern void func_02051794(int, int *, int, int, int);
extern int func_020ea1bc(int, int);
extern void NNS_FndInitList(int, int);

extern unsigned char data_021c8194[];
extern unsigned char data_021fbe94[];

extern unsigned char data_021c81bc[];
extern unsigned char data_021c81d4[];
extern unsigned char data_021c8230[];
extern unsigned char data_021c828c[];
extern unsigned char data_021c82e8[];

void func_020514dc(void)
{
    int result;

    func_02051794((unsigned int) data_021c8230, &data_020dcf88, 0, 0, 0);
    func_02051794((unsigned int) data_021c828c, &data_020dcf90, 0, 0, 0);
    func_02051794((unsigned int) data_021c82e8, &data_020dcf98, 0, 0, 0);
    func_02051794((unsigned int) data_021c81d4, &data_020dcfa0, 0, 0, 0);

    result = func_020ea1bc(0x1800, *((int *) data_021fbe94));
    *((int *) data_021c8194) = result;

    if (result) {
        NNS_FndInitList((unsigned int) data_021c81bc, 8);
    }
}
