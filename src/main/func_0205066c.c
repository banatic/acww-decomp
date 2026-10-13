/* func_0205066c @ 0x0205066c, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x44];
    int unk_44;
    char pad_48[8];
} Elem;
extern Elem *data_021c8184;
extern void func_0209d238(void *, void *);
extern void func_0209d0a4(void *);
extern void func_0200451c(void *);

int func_0205066c(void *p0, int idx)
{
    int result = 0;
    if (data_021c8184 == 0) {
        return result;
    }
    if (idx == -1) {
        goto ret0;
    }
    {
        char *base = (char *) data_021c8184 + 0x50;
        Elem *e = (Elem *) (base + idx * 0x16c);
        e->unk_44 = 2;
        func_0209d238((char *) p0 + 0x600, (char *) e + 0x48);
        func_0209d0a4((char *) e + 0x4c);
        func_0200451c(e);
        result = 1;
    }
ret0:
    return result;
}
