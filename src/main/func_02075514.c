/* func_02075514 @ 0x02075514, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_02073d68(void *arg);
extern void func_02073d6c(void *arg, unsigned char byte);

void func_02075514(unsigned char *payload, unsigned int length, int player)
{
    void *value;
    value = data_020ccf94;
    if (func_02073d68(value) == 3) {
        func_02073d6c(value, *payload);
    }
}
