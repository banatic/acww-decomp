/* func_0205be64 @ 0x0205be64, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(void *);
extern void func_0209e140(void *, int);

void func_0205be64(unsigned char *out)
{
    unsigned int buffer[2];
    buffer[0] = 0;
    buffer[1] = 0;
    func_0209e474(buffer);
    if (((unsigned char *) buffer)[2] < 6) {
        func_0209e140(buffer, 1);
    }
    out[0] = ((unsigned char *) buffer)[3];
    out[1] = ((unsigned char *) buffer)[4];
    out[2] = ((unsigned char *) buffer)[5];
}
