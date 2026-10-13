/* func_02076568 @ 0x02076568, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern unsigned int data_021e5a2c;

void func_020736bc(const void *src, void *dst, unsigned int size);
void func_0207835c(unsigned int *key, unsigned short *arr, void *buf);
void *func_0207cec0(void *table, unsigned int key);
unsigned short *func_0207dfd4(void *handle, unsigned int index);

void func_02076568(void)
{
    unsigned int key;
    unsigned short arr[4];
    char buf[9];
    void *handle;
    int i;
    unsigned short *p;

    arr[0] = 0xFFF1;
    arr[1] = 0xFFF1;
    arr[2] = 0xFFF1;
    arr[3] = 0xFFF1;

    func_020736bc(data_020ccf94, buf, 9);
    func_0207835c(&key, arr, buf);

    handle = func_0207cec0(&data_021e5a2c, key);
    if (handle) {
        for (i = 0; i < 4; i++) {
            p = func_0207dfd4(handle, i);
            if (p) {
                *p = arr[i];
            }
        }
    }
}
