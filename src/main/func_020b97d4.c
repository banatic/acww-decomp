/* func_020b97d4 @ 0x020b97d4, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[2];
    unsigned short unk_02;
} Header;

extern void func_020b9808(void *b, unsigned short value, int c);

void func_020b97d4(Header *a, void *b, int c)
{
    func_020b9808(b, a->unk_02, c);
}
