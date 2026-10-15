/* func_020c2640 @ 0x020c2640, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201ad18(void *a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);
extern int func_02019d0c(void *a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11);
extern int data_020c814c;
extern unsigned short data_020c80f8;

extern unsigned char data_021fbee8[];

int func_020c2640(void *obj)
{
    *(int *) ((char *) obj + 0x4e8) |= 2;
    func_0201ad18((char *) obj + 0x3b0, 1, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
    func_02019d0c((char *) obj + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
