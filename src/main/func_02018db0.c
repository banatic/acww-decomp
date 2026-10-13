/* func_02018db0 @ 0x02018db0, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02019de4(void *, void *);
extern void func_0201b1a4(void *, void *, int, int, int);
extern void func_02016764(void *, void *, int, int, int, int, int, int);
extern void func_0201b044(void *, void *);
extern void func_0201afd4(void *, void *);
extern void func_0201b350(void *, int);
extern void func_02019af0(void *, int);

extern unsigned char data_021fbee8[];

int func_02018db0(void *p0, void *p1)
{
    void *t;
    t = func_02019de4(p0, p1);
    func_0201b1a4((void *) ((char *) p1 + 0x350), p1, 0, 0, *(unsigned short *) ((char *) t + 0x1c));
    func_02016764((void *) ((char *) p1 + 0x334), p1, 0xd8, *(unsigned short *) ((char *) t + 0x1c), 0, 0x1000, 0, 0);
    func_0201b044((void *) ((char *) p1 + 0x350), (void *) data_021fbee8);
    func_0201afd4((void *) ((char *) p1 + 0x350), (void *) data_021fbee8);
    func_0201b350((void *) ((char *) p1 + 0x3aa), -2);
    func_02019af0(p0, 0);
    return 0;
}
