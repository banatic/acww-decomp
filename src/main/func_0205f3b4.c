/* func_0205f3b4 @ 0x0205f3b4, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_020b65c4(void);
extern unsigned int func_020b5e04(unsigned int);
extern unsigned int func_020b5df8(unsigned int);
extern unsigned int func_02085f08(void);
extern unsigned int func_0205f63c(void);
extern unsigned int func_020ea0e0(unsigned int, unsigned int);
extern unsigned int data_021c9acc;
extern unsigned char *data_020ccf94;
typedef struct {
    char pad_00[0x24];
    unsigned int arr[1];
} UnkStruct_0205f3b4;
void func_0205f3b4(UnkStruct_0205f3b4 *data)
{
    unsigned int g = data_021c9acc;
    unsigned char cnt = data_020ccf94[0x6C];
    unsigned int i;
    unsigned int count;
    unsigned int a;
    unsigned int b;
    unsigned int end;
    count = func_020b5e04((unsigned int) func_020b65c4());
    if (cnt < count) {
        count = cnt;
    }
    for (i = 0; i < count; i++) {
        data->arr[i] = func_020ea0e0(func_0205f63c(), g);
    }

    if (count == 0) {
        count = 1;
    }
    a = func_020b5df8((unsigned int) func_020b65c4());
    b = func_02085f08();
    end = (a + b) - count;
    end = end + 4;
    for (i = 4; i < end; i++) {
        data->arr[i] = func_020ea0e0(func_0205f63c(), g);
    }
}
