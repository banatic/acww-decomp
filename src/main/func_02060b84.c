/* func_02060b84 @ 0x02060b84, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02060f04(void *, int);
extern void *func_02061188(void);
extern void __register_global_object(void *, void *, void *);
extern void func_020051b0(void);

extern unsigned char data_021ebcd4;
extern unsigned short data_021cb4f4;
extern unsigned int data_021cb4fc;
extern unsigned char data_021cb564;

void *func_02060b84(int param)
{
    if (func_02060f04(&data_021ebcd4, param) != 0) {
        return func_02061188();
    }
    if (!(data_021cb4fc & 1)) {
        data_021cb4f4 = 0xfff1;
        __register_global_object(&data_021cb4f4, (void *) func_020051b0, &data_021cb564);
        data_021cb4fc |= 1;
    }
    return &data_021cb4f4;
}
