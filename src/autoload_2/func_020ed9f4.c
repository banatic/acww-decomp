/* func_020ed9f4 @ 0x020ed9f4, 0xb4 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#pragma arm

typedef struct {
    int a;
    int b;
    unsigned short c;
    unsigned char pad_0A[6];
} Entry;

extern int OS_ReadMessage(void *q, int *msg, int flags);
extern void func_020ed950(void *arg);
extern int func_ov066_022698ec(int, int, unsigned short, void (*)(void *));

#pragma thumb
extern int func_ov065_0227ee74(unsigned char, int, int);
#pragma arm

extern unsigned char data_021fbef8;
extern Entry data_021fc120[];
extern int data_021fbf98;

int func_020ed9f4(void)
{
    int msg;
    unsigned char s;
    Entry *e;

    if (OS_ReadMessage(&data_021fbf98, &msg, 0) != 0) {
        e = &data_021fc120[msg];
        s = data_021fbef8;

        if ((unsigned char) (s + 0xff) <= 1) {
            return func_ov066_022698ec(e->a, e->b, e->c, func_020ed950);
        }

        if ((unsigned char) (s + 0xfd) <= 1) {
            return func_ov065_0227ee74((unsigned char) e->c, e->a, e->b);
        }
    }
    return 0;
}