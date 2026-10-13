/* func_ov003_0221c570 @ 0x0221c570, 0x18 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221c588(void);
extern int data_ov003_02238908[];

int func_ov003_0221c570(void)
{
    int index;
    int value;

    index = func_ov003_0221c588();
    value = data_ov003_02238908[index];
    return value;
}
