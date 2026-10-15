/* func_020ed874 @ 0x020ed874, 0x80 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int OS_SendMessage(void *mq, int msg, int flags);
extern int data_021fbf98;
struct Entry {
    unsigned int a;
    unsigned int b;
    unsigned short c;
    unsigned short pad_0A;
    unsigned int d;
};
extern struct Entry data_021fc120[16];

int func_020ed874(unsigned int p0, unsigned int p1, unsigned short p2, unsigned int p3)
{
    unsigned int i;
    int found = 0;
    for (i = 0; i < 16; i++) {
        if (data_021fc120[i].a == 0) {
            data_021fc120[i].a = p0;
            data_021fc120[i].b = p1;
            data_021fc120[i].c = p2;
            data_021fc120[i].d = p3;
            OS_SendMessage(&data_021fbf98, i, 0);
            found = 1;
            break;
        }
    }
    return found;
}
