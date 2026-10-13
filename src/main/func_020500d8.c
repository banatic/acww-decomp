/* func_020500d8 @ 0x020500d8, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *data_021c8184; // 0x021c8184
extern int data_020dcd78;            // 0x020dcd78
extern void func_0205510c(void *a, void *b);

typedef struct {
    char pad_00[0x44];
    int type; // 0x44
    char pad_48[0x98 - 0x48];
    char data[0x150 - 0x98]; // 0x98
    int val0;                // 0x150
    int val1;                // 0x154
    int val2;                // 0x158
    char pad_15C[0x16c - 0x158 - 4];
} Entry;

int func_020500d8(void)
{
    Entry *p;
    int i;
    int buf[3];

    if (data_021c8184 == 0) {
        return 0;
    }

    p = (Entry *) (data_021c8184 + 0x50);
    i = 0;
    while (i < data_020dcd78) {
        if (p->type == 3) {
            buf[0] = p->val0;
            buf[1] = p->val1;
            buf[2] = p->val2;
            func_0205510c(p->data, buf);
        }
        p = (Entry *) ((char *) p + 0x16c);
        i++;
    }
    return 1;
}
