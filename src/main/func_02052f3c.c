/* func_02052f3c @ 0x02052f3c, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b67e8(int);
extern int func_020b6818(int);
extern int func_02060ee0(int, int);
extern int func_02061220(int);
extern int func_020b6694(int);
extern int func_020b66c4(int);
extern int func_020b6744(int);
extern int func_020b6774(int);

typedef struct {
    char data[0x48];
} UnkStruct_02052f3c;

extern UnkStruct_02052f3c data_021c89fc[];
extern UnkStruct_02052f3c data_021c884c[];
extern UnkStruct_02052f3c data_021c87b4;

extern unsigned char data_021ebcd4[];

int func_02052f3c(int param)
{
    if (func_020b67e8(param)) {
        int a = func_02060ee0((unsigned int) data_021ebcd4, func_020b6818(param));
        if (a) {
            return func_02061220(a);
        }
    } else {
        if (func_020b6694(param)) {
            return (int) &data_021c89fc[func_020b66c4(param)];
        } else {
            if (func_020b6744(param)) {
                return (int) &data_021c884c[func_020b6774(param)];
            } else {
                if (param == 10) {
                    return (int) &data_021c87b4;
                }
            }
        }
    }
    return 0;
}
