/* func_0208b77c @ 0x0208b77c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b45d0(void *p1, void *p2, int p3, int p4, int p5, int p6);

typedef struct UnkStruct_0208b77c {
    char pad_00[0x7c];
    void *unk_7C;
} UnkStruct_0208b77c;

void func_0208b77c(UnkStruct_0208b77c *a)
{
    func_020b45d0((char *) a + 0x3c, a->unk_7C, 7, 0, 0, 1);
}
