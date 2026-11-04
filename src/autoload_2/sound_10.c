/* sound_10: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020eefd4 @ 0x020eefd4, 0x34 bytes, ARM
 * func_020eef80 @ 0x020eef80, 0x54 bytes, ARM
 */

struct UnkStruct020eefd4 {
    unsigned char pad_00[0x15];
    unsigned char unk_15;
    unsigned char pad_16[6];
    int unk_1C;
};

extern void OS_Terminate(void);
extern void func_020eec60(int);
extern unsigned long func_020efc18(const unsigned long *p);
extern void func_020ef284(int node);
extern void *func_020efc2c(void *list, void *object);

void func_020eefd4(struct UnkStruct020eefd4 *self)
{
    if (self->unk_15 == 0xff) {
        OS_Terminate();
    }
    if (self->unk_1C == 0xff) {
        return;
    }
    func_020eec60(self->unk_1C);
}

void func_020eef80(void *list)
{
    void *node;
    if (list == 0) {
        OS_Terminate();
    }
    node = (void *) func_020efc18((const unsigned long *) list);
    if (node == 0) {
        return;
    }
    do {
        func_020ef284((int) node);
        node = func_020efc2c(list, node);
    } while (node != 0);
}
