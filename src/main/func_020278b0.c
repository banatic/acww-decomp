/* func_020278b0 @ 0x020278b0, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int);
extern int func_020036e8(int);
extern void func_0202da38(void *, void *, void *, int, int, int, int, int, int);
typedef struct {
    int unk_00;
    unsigned char unk_04;
} GlobalData;
extern GlobalData data_020c8ba8;

void func_020278b0(void *s, void *out)
{
    func_0202da38(s, (char *) s + 0x104, (char *) s + 0x122, 0x1e,
                  func_020036e8(func_0208150c(*(int *) (*(int *) ((char *) s + 0x100) + 0x830))), data_020c8ba8.unk_00,
                  data_020c8ba8.unk_04, 0, 0);
    *(void **) out = (char *) s + 0x104;
    *(unsigned char *) ((char *) out + 4) = *(unsigned char *) ((char *) s + 0x122);
}
