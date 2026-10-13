/* func_0201cbcc @ 0x0201cbcc, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020044d0(void *a, unsigned int *b);

typedef struct {
    char pad_00[0x5c];
    unsigned int unk_5C;
    unsigned int unk_60;
    unsigned int unk_64;
} UnkStruct_0201cbcc;

void func_0201cbcc(void *arg, UnkStruct_0201cbcc *p)
{
    unsigned int arr[3];
    unsigned int *base;

    base = (unsigned int *) ((char *) p + 0x5c);
    arr[0] = p->unk_5C;
    arr[1] = base[1];
    arr[2] = base[2];
    func_020044d0(arg, arr);
}
