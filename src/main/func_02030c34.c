/* func_02030c34 @ 0x02030c34, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02034714(void *);
extern void func_0203242c(void *);
extern void func_020326b0(void *);
extern void func_020346fc(void *);

extern char data_021c31ec[];
extern char data_021c3fe8[];
extern char data_021c49e8[];
extern char data_021c4c78[];
extern char data_021c4c79[];
extern char data_021c5124[];

void func_02030c34(int param)
{
    func_02034714(data_021c31ec + 0x138 * param);
    *(int *) (data_021c3fe8 + 0x44) = 0;
    *(int *) (data_021c49e8 + 0x48) = 0;
    *(int *) (data_021c49e8 + 0x4c) = 0;
    func_0203242c(data_021c4c78);
    func_020326b0(data_021c4c79);
    func_020346fc(data_021c5124);
}
