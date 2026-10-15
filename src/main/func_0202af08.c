/* func_0202af08 @ 0x0202af08, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int arg);
extern int func_020036e8(int arg);
extern int func_0202da38(void *a, void *b, void *c, int d, int e, int f, int g, int h, int i);

struct GlobalData {
    int word;
    unsigned char byte;
};
extern struct GlobalData data_020c8b18;

void func_0202af08(unsigned char *a, unsigned char *b)
{
    func_0202da38(a, a + 0x104, a + 0x122, 0x1e,
                  func_020036e8(func_0208150c(*(unsigned int *) (*(unsigned int *) (a + 0x100) + 0x830))), data_020c8b18.word,
                  4, 1, data_020c8b18.byte);
    *(unsigned int *) b = (unsigned int) (a + 0x104);
    *(unsigned char *) (b + 4) = *(unsigned char *) (a + 0x122);
}
