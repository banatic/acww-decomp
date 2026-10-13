/* func_020a9708 @ 0x020a9708, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02064658(void *a, void *b, int c, int d);
extern int func_020a9ae8(void *p);
extern int func_020a9ae4(void *p);
extern int data_021f4428[2];
extern int data_021f4458[2];

int func_020a9708(char *arg)
{
    func_02064658(arg + 0x44, data_021f4428, 12, data_021f4458[1] + 0x20);
    data_021f4428[0] = func_020a9ae8(data_021f4428);
    data_021f4428[1] = func_020a9ae4(&data_021f4428[1]);
    if (data_021f4428[0] == 0x44415431) {
        return 1;
    } else {
        return 0;
    }
}
