/* func_020b983c @ 0x020b983c, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

class Task {
  public:
    virtual int run();
    char link[8];
    unsigned char unk_0C;
    unsigned char state;
    unsigned char unk_0E;
    unsigned char cost;
};

extern "C" int func_020e8ce0(void *list, void *p);

extern unsigned char data_021f6c98[];

extern "C" void func_020b983c(void)
{
    void *p;
    volatile unsigned short *vc;
    unsigned char two;
    void *list;
    unsigned int ok;

    p = *(void **) data_021f6c98;
    if (p != 0) {
        p = (char *) p - 4;
    }
    vc = (volatile unsigned short *) 0x04000006;
    two = 2;
    list = (void *) data_021f6c98;
    while (p != 0) {
        Task *t = (Task *) p;
        if (*vc + t->cost > 260) {
            break;
        }
        ok = (t->state == 1) ? 1 : 0;
        if (ok != 0) {
            if (t->run() != 0) {
                t->state = two;
            }
        }
        if (p != 0) {
            p = (char *) p + 4;
        }
        func_020e8ce0(list, p);
        p = *(void **) list;
        if (p != 0) {
            p = (char *) p - 4;
        }
    }
}
