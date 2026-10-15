/* func_02045db8 @ 0x02045db8, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct Entry;
struct Header {
    unsigned char code : 3;
};
struct Entry {
    unsigned char b0 : 3;
    unsigned char : 5;
    unsigned char : 7;
    unsigned char b1 : 1;
    unsigned char pad_02[14];
};
extern struct Entry data_021c7884[];
extern void func_0204622c(void *);

void func_02045db8(struct Header *h)
{
    struct Entry *p;
    int i;

    p = data_021c7884;
    i = 0;
    do {
        if (p->b0 == h->code && p->b1) {
            p->b1 = 0;
        }
        p++;
        i++;
    } while (i < 20);

    func_0204622c(h);
}
