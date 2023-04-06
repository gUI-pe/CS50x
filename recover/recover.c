#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Make sure program was run with just one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    typedef uint8_t  BYTE;
    BYTE buffer[512];
    FILE *c = fopen(argv[1], "r");
    
    //checking if c opens
    if (c == NULL)
    {
        printf("forensic image cannot be opened for reading\n");
    }

    int jpegs = 0;
    char filename[8];
    FILE *img = NULL;
    while (fread(buffer, 1, 512, c) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (jpegs == 0)
            {
                sprintf(filename, "%03i.jpg", jpegs);
                img = fopen(filename, "w");
                fwrite(buffer, 1, 512, img);
                jpegs++;
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", jpegs);
                img = fopen(filename, "w");
                fwrite(buffer, 1, 512, img);
                jpegs++;
            }
        }
        else if (jpegs >= 1)
        {
            fwrite(buffer, 1, 512, img);
        }
    }
    fclose(img);
    fclose(c);
}