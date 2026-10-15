/* func_0201e734 @ 0x0201e734, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,p
 */

extern void func_0209e474(void *);
extern unsigned int func_0208150c(int);
extern int func_020036e8(unsigned char *);
extern int func_0202da38(void *, void *, void *, int, int, void *, int, int, int);

struct GlobalInfo {
    void *ptr;
    unsigned char unk_04;
};
extern struct GlobalInfo data_020c8b50;

void func_0201e734(void *a, void *b)
{
    struct {
        unsigned char byte0;
        unsigned char byte1;
        unsigned char byte2;
        unsigned char byte3;
        unsigned int word4;
    } local;
    int r4;
    int val1;
    int val2;
    void *p;
    *(unsigned int *) &local.byte0 = 0;
    local.word4 = 0;

    func_0209e474(&local);
    if ((unsigned int) local.byte2 < 12) {
        r4 = 0;
    } else if ((unsigned int) local.byte2 < 17) {
        r4 = 2;
    } else {
        r4 = 4;
    }

    p = *(void **) ((char *) a + 0x100);
    val2 = *(int *) ((char *) p + 0x830);

    val1 = func_020036e8((unsigned char *) func_0208150c(val2));

    func_0202da38(a, (char *) a + 0x104, (char *) a + 0x122, 30, val1, data_020c8b50.ptr, 1, r4, data_020c8b50.unk_04);

    *(void **) b = (char *) a + 0x104;
    *((unsigned char *) b + 4) = *((unsigned char *) a + 0x122);
}
