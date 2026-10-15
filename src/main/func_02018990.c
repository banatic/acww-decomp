/* func_02018990 @ 0x02018990, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019de4(void *a);
extern void func_0201b1a4(void *a, void *b, int c, int d, unsigned short e);
extern void func_0201b044(void *a, void *b);
extern void func_0201afd4(void *a, void *b);
extern void func_0201b350(void *a, int b);
extern void func_02016764(void *a, void *b, unsigned int c, unsigned short d, unsigned int e, unsigned int f, unsigned short g,
                          int h);
extern void func_02019a18(void *a, unsigned int b, unsigned char c, unsigned short d, unsigned short e);
extern void func_02019af0(void *a, int b);
extern unsigned short data_020c80f8;

extern unsigned char data_021fbee8[];

int func_02018990(void *a, void *b)
{
    void *r4;

    r4 = (void *) func_02019de4(a);
    func_0201b1a4((char *) b + 0x350, b, 0, 0, data_020c80f8);
    func_0201b044((char *) b + 0x350, (void *) data_021fbee8);
    func_0201afd4((char *) b + 0x350, (void *) data_021fbee8);
    func_0201b350((char *) b + 0x3aa, -2);
    func_02016764((char *) b + 0x334, b, *(unsigned int *) r4, *(unsigned short *) ((char *) r4 + 0x1c),
                  *((unsigned char *) r4 + 0x20), 0x1000, *(unsigned short *) ((char *) r4 + 0x1e), 0);
    *((unsigned char *) a + 4) = (unsigned char) (*(unsigned int *) ((char *) a + 0x1c));
    *((unsigned char *) a + 5) = (unsigned char) (*(unsigned int *) ((char *) a + 0x14));
    func_02019a18((char *) a + 6, *(unsigned int *) r4, *((unsigned char *) r4 + 0x20),
                  *(unsigned short *) ((char *) r4 + 0x1c), *(unsigned short *) ((char *) r4 + 0x1e));
    func_02019af0(a, 0);
    return 1;
}
