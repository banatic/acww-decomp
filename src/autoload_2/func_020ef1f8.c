/* func_020ef1f8 @ 0x020ef1f8, 0x40 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x36];
    unsigned char count;
} Header;

extern void OS_Terminate(void);
extern void func_020ef918(void *elem, int arg);

void func_020ef1f8(Header *p, int index, int arg)
{
    void *e;

    e = (void *) ((char *) p + 8 + index * 12);
    if (index >= p->count) {
        OS_Terminate();
    }
    func_020ef918(e, arg);
}
