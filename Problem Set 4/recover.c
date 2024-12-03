#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Assuming block size is 512 (given)
const int BLOCK = 512;
// Reference from filter bmp.h
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./recover [raw file]\n");
        return 1;
    }

    // Check if file exist
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // If file exist
    BYTE buffer[BLOCK];
    int count = 0;
    FILE *image = NULL;

    // Hint given
    // while (fread(buffer, 1, 512, card) == 512)
    while (fread(buffer, sizeof(BYTE), BLOCK, file) == BLOCK)
    {
        // Goal is to create JPEGs
        // https://en.wikipedia.org/wiki/JPEG
        // Reference under "Syntax and structure"
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && (buffer[2] == 0xFF && buffer[3] >= 0xE0))
        {
            // Check if image is open, avoid leak
            if (image != NULL)
            {
                fclose(image);
            }

            // Note: Don’t forget the NUL character
            // 8 characters [0][3][d][.][j][p][g][\0]
            // Example: [0][0][1][.][j][p][g][\0]
            char fname[8];
            sprintf(fname, "%03d.jpg", count);

            // Create file
            image = fopen(fname, "w");

            // Throw error if it fails to create
            if (image == NULL)
            {
                printf("Failed to create %s\n", fname);
                return 2;
            }

            count++;
        }

        // If everything is clear above, let's write the image
        if (image != NULL)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK, image);
        }
    }

    // Avoid leaks
    if (image != NULL)
    {
        fclose(image);
    }

    fclose(file);

    return 0;
}
