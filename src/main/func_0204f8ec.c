/* func_0204f8ec @ 0x0204f8ec, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Entry {
    unsigned char type;
    unsigned char count;
    unsigned char pad_02[10];
};

extern struct Entry data_021c80f4[12];
extern void OS_Terminate(void);
extern void func_0204f9ec(struct Entry *);

void func_0204f8ec(unsigned char key)
{
    struct Entry *p = 0;
    unsigned int i = 0;
    goto test;
loop: {
    struct Entry *e = &data_021c80f4[i];
    if (e->type == key) {
        p = e;
        if (e->count != 0) {
            e->count--;
        }
    }
}
    i++;
test:
    if (i < 12) {
        goto loop;
    }

    if (p == 0) {
        OS_Terminate();
    }

    if (p->count == 0) {
        func_0204f9ec(p);
    }
}
