/* func_02023be0 @ 0x02023be0, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(void *, void *, void *, int, int, int, int, int, int);

extern struct {
    int a;
    unsigned char b;
} data_020c8c08;

struct UnkStruct_02023be0 {
    void *unk_00;
    unsigned char unk_04;
};

void func_02023be0(void *arg0, struct UnkStruct_02023be0 *out)
{
    func_0202da38(arg0, (char *) arg0 + 0x104, (char *) arg0 + 0x122, 30,
                  func_020036e8(func_0208150c(*(int *) ((char *) *(void **) ((char *) arg0 + 0x100) + 0x830))),
                  data_020c8c08.a, data_020c8c08.b, 0, 0);
    out->unk_00 = (char *) arg0 + 0x104;
    out->unk_04 = *(unsigned char *) ((char *) arg0 + 0x122);
}
