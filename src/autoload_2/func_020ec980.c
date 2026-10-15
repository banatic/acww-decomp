/* func_020ec980 @ 0x020ec980, 0x200 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef struct S1f8 {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char unk_02;
} S1f8;

extern unsigned short data_021fbefc;
extern int data_021fbf5c;
extern int data_0213e744;
extern int data_0213e6bc;
extern int data_0213e6c4;
extern int data_0213e750;
extern int data_021fbf3c;
extern int data_021fbf40;
extern int data_021fc220;
extern void func_020ed3d4(int result, int index, int user_data);
extern unsigned char data_021fbef8;
extern void func_020ed144(unsigned short value, int index);
extern S1f8 data_021fbff8;

extern int func_ov065_0227f46c(void *p);
extern void DWC_SetAuthServer(int n);
extern void DWC_ConnectInetAsync(void);
extern int func_ov065_0227f380(void);
extern int DWC_GetInetStatus(void);
extern int func_ov065_0227f720(void *p);
extern void func_ov065_022782d4(void *a, int b, int c, void *d, void *e, int f, int g, int h, int i);
extern void func_ov065_02277f98(int a, int b, void (*callback)(int, int, int), int d);
extern void DWC_SetSendSplitMax(int n);
extern void *func_ov065_0227ecf0(void (*callback)(unsigned short, int));
extern void func_020ecfec(void);
extern int func_020ec1f8(void);

int func_020ec980(void)
{
    switch (data_021fbefc) {
        case 0:
            func_ov065_0227f46c(&data_021fbf5c);
            DWC_SetAuthServer(2);
            DWC_ConnectInetAsync();
            data_021fbefc = 1;
            break;
        case 1:
            if (func_ov065_0227f380() != 0) {
                if (DWC_GetInetStatus() == 4) {
                    data_021fbefc = 2;
                }
            }
            break;
        case 2:
            func_ov065_0227f720(&data_0213e744);
            data_0213e6bc = 1;
            data_0213e6c4 = 1;
            func_ov065_022782d4(&data_021fc220, data_021fbf40 + 0x20, 0x299e, &data_0213e744, &data_0213e750, 0, 0,
                                data_021fbf3c, 0x20);
            func_ov065_02277f98(0, 0, &func_020ed3d4, 0);
            data_021fbefc = 3;
            break;
        case 3:
            if (data_0213e6c4 == 0) {
                data_0213e6c4 = 1;
                data_021fbefc = 4;
            }
            break;
        case 4:
            if (data_021fbef8 == 3) {
                data_0213e6c4 = 0;
            }
            if (data_0213e6c4 == 0) {
                DWC_SetSendSplitMax(0x100);
                func_ov065_0227ecf0(&func_020ed144);
                func_020ecfec();
                data_021fbefc = 5;
            }
            break;
        case 5:
            if (data_021fbef8 != 4) {
                goto ret1;
            }
            if ((func_020ec1f8() & 1) != 0) {
                if (data_021fbff8.unk_02 <= 0x1e) {
                    goto ret1;
                }
            }
            return 0;
        ret1:
            return 1;
    }
    return 0;
}
