/* func_0202a5e8 @ 0x0202a5e8, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct Data020c8af0 {
    unsigned int unk_00;
    unsigned char unk_04;
} data_020c8af0;
extern struct UnkStruct_0202a5e8 {
    void *unk_00;
    unsigned char unk_04;
} out;
extern unsigned int func_0208150c(unsigned int);
extern unsigned int func_020036e8(unsigned char *);
extern int func_0202da38(void *, void *, void *, int, int base, int offset, int scale, int, int);

void func_0202a5e8(void *a, struct UnkStruct_0202a5e8 *out)
{
    unsigned int v0;
    unsigned int v4;
    unsigned int v8;

    v0 = func_020036e8((unsigned char *) func_0208150c(
        *(unsigned int *) ((unsigned char *) (*(void **) ((unsigned char *) a + 0x100)) + 0x830)));
    v4 = data_020c8af0.unk_00;
    v8 = data_020c8af0.unk_04;
    func_0202da38(a, (unsigned char *) a + 0x104, (unsigned char *) a + 0x122, 0x1e, v0, v4, v8, 0, 0);
    out->unk_00 = (unsigned char *) a + 0x104;
    out->unk_04 = *(unsigned char *) ((unsigned char *) a + 0x122);
}
