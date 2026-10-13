/* func_020ed8f4 @ 0x020ed8f4, 0x5c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad[0x40];
} OSQ;
extern OSQ data_021fbf98;
extern int OS_ReceiveMessage(void *, void *, int);
typedef struct {
    int unk_00;
    unsigned char pad[12];
} Entry16;
extern Entry16 data_021fc120[16];

void func_020ed8f4(void)
{
    void *msg;
    unsigned int i;
    do {
    } while (OS_ReceiveMessage(&data_021fbf98, &msg, 0) != 0);
    for (i = 0; i < 0x10; i++) {
        data_021fc120[i].unk_00 = 0;
    }
}
