/* func_020a855c @ 0x020a855c, 0x66 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020a855c {
    int unk_00;
    int size;
} UnkStruct_020a855c;
typedef struct Hdr {
    unsigned char pad_00[8];
    int unk_08;
    int unk_0C;
} Hdr;

extern int func_020a86e4(Hdr *h, unsigned char *p0, unsigned char *p1, unsigned char *p2);
extern int func_020a8a34(UnkStruct_020a855c *e, int off);

int func_020a855c(Hdr *h, unsigned char *o0, UnkStruct_020a855c *e0, unsigned char *o1, UnkStruct_020a855c *e1,
                  unsigned char *o2, UnkStruct_020a855c *e2)
{
    unsigned char t[8];
    UnkStruct_020a855c *arr[3];
    int off;
    int total;
    int i;
    int n;

    func_020a86e4(h, &t[0], &t[1], &t[2]);
    *o0 = t[0];
    *o1 = t[1];
    *o2 = t[2];
    arr[0] = e0;
    arr[1] = e1;
    arr[2] = e2;
    off = h->unk_0C + h->unk_08 + 2;
    total = 2;
    for (i = 0; i < 3; i++) {
        func_020a8a34(arr[i], off);
        n = arr[i]->size + 2;
        total = total + n;
        off = off + n;
    }
    return total;
}
