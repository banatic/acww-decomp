/* func_020506c0 @ 0x020506c0, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Elem {
    unsigned char pad_00[0x44];
    int unk_44;
} Elem;

extern Elem *data_021c8184;
extern int data_020dcd78;

int func_020506c0(void)
{
    int result;
    int i;
    Elem *p;
    int count;

    i = 0;
    result = -1;
    p = data_021c8184;
    if (p) {
        p = (Elem *) ((char *) p + 0x50);
        count = data_020dcd78;
        while (i < count) {
            if (p->unk_44 == 0) {
                result = i;
                p->unk_44 = 1;
                break;
            }
            p = (Elem *) ((char *) p + 0x16c);
            i++;
        }
    }
    return result;
}
