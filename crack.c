#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include "sha256.h"

#define FILE_SIZE_4 320
#define FILE_SIZE_6 640

#define FILE_NAME_4 "pwd4sha256"
#define FILE_NAME_6 "pwd6sha256"

/* read hashfile and return content
 * modified code from https://stackoverflow.com/a/22059317 */
char *read_hash_file(char *file_name){
    FILE *fp;
    char *buffer;
    long filelen;
    fp = fopen(file_name, "rb");

    /* get file length by jump to the end of file */
    fseek(fp, 0, SEEK_END);
    filelen = ftell(fp);

    /* jump back to the beginning and read entire file */
    rewind(fp);
    buffer = (char *)malloc((filelen+1)*sizeof(char));
    fread(buffer, filelen, 1, fp);
    fclose(fp);
    return buffer;
}

/* return the length of a hash file
 * modified code from https://stackoverflow.com/a/22059317 */
int hash_file_length(char *file_name){
    FILE *fp;
    long filelen;
    fp = fopen(file_name, "rb");

    /* get file length by jump to the end of file */
    fseek(fp, 0, SEEK_END);
    filelen = ftell(fp);
    fclose(fp);
    return filelen;
}

/* get one line in file and return that line as string
 * modified from
 * https://sucs.org/Knowledge/Help/Program%20Advisory/Reading%20an%20arbitrarily%20long%20line%20in%20C#scanf */
char *get_line(FILE *f) {
    size_t size = 0;
    size_t len  = 0;
    size_t last = 0;
    char * buf  = NULL;

    do {
        size += BUFSIZ; // BUFSIZ is defined as "the optimal read size for this platform"
        buf = realloc(buf,size); // realloc(NULL,n) is the same as malloc(n)
        /* Actually do the read. Note that fgets puts a terminal '\0' on the
           end of the string, so we make sure we overwrite this */
        fgets(buf+last,size,f);
        len = strlen(buf);
        last = len - 1;
    } while (!feof(f) && buf[last]!='\n');

    /* add \0 at the end of string */
    if(buf != NULL) {
        buf[last] = '\0';
    }
    return buf;
}

/* crack four characters password, generate guess, hash guess and compare to hashes in file */
void four(){
    /* search the string generated from the count.py */
    /* the order of the search is by the frequency occurred in common_passwords.txt and add upper case*/
//    char *search = "earonistlcdmhgbup1ykfw2vj3z04596x78q*?.-+&\\;\'!ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//    char *search = "eEaArRoOnNiIsStTlLcCdDmMhHgGbBuUpP1yYkKfFwW2vVjJ3zZ04596xX78qQ*?.-+&\\;\'!";

    /* the order of the search is by the frequency occurred in pf4.txt (pf means passord found)*/
    char *search = "5e4usngda6zwtokihA";

    char *buffer;
    buffer = read_hash_file(FILE_NAME_4);

    int i, j, k, x, y;
    int start, finish;

    BYTE buf[SHA256_BLOCK_SIZE];

    BYTE password_guess[5];
    password_guess[4] = '\0';

    SHA256_CTX ctx;
    start = 0;
    finish = strlen(search);

    for (j = start; j < finish; j++){
        password_guess[0] = search[j];
        for (k = start; k < finish; k++){
            password_guess[1] = search[k];
            for (x = start; x < finish; x++){
                password_guess[2] = search[x];
                for (y = start; y < finish; y++){
                    password_guess[3] = search[y];
                    sha256_init(&ctx);
                    sha256_update(&ctx, password_guess, 4);
                    sha256_final(&ctx, buf);
                    /* compare password_guess with all hashes */
                    for (i = 0; i < FILE_SIZE_4; i = i + 32) {
                        if (!memcmp(buffer+i, buf, SHA256_BLOCK_SIZE)){
                            printf("%s %d\n",password_guess, i/32+1);
                            break;
                        }
                    }
                }
            }
        }
    }

}

/* crack six characters password, generate guess, hash guess and compare to hashes in file */
void six(){
    /* search the string generated from the count.py */
    /* the order of the search is by the frequency occurred in common_passwords.txt and add upper case*/
//    char *search = "earonistlcdmhgbup1ykfw2vj3z04596x78q*?.-+&\\;\'!ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//    char *search = "eEaArRoOnNiIsStTlLcCdDmMhHgGbBuUpP1yYkKfFwW2vVjJ3zZ04596xX78qQ*?.-+&\\;\'!";

    /* the order of the search is by the frequency occurred in pf6.txt (pf means passord found)*/
//    char *search = "ioestnlcua^r1pd2zyhbkgfYSPC95*";
    char *search = "niabcdefghjklmopqrstuvwxyz";

    char *buffer;
    buffer = read_hash_file(FILE_NAME_6);

    int not_found[20];
//    int found[20];
    int num_found = 0;
    int num_not_found = 20;




    int i, j, k, x, y, w, z, b, c;
    int start, finish;
    int num_password;

//    found[0] = -1;
//    /* initialize found and not_found */
//    for (i = 0; i < FILE_SIZE_6 / 32; i++) {
//        found[i] = -1;
//        not_found[i] = i * 32;
//    }

//    int a;
//    /* record the password already found to reduce comparation */
//    found[num_found] = 13;
//    num_found = num_found + 1;
//    found[num_found] = 19;
//    num_found = num_found + 1;
//    found[num_found] = 18;
//    num_found = num_found + 1;
//    found[num_found] = 20;
//    num_found = num_found + 1;
//    found[num_found] = 14;
//    num_found = num_found + 1;
//    found[num_found] = 11;
//    num_found = num_found + 1;
//    found[num_found] = 29;
//    num_found = num_found + 1;
//    found[num_found] = 12;
//    num_found = num_found + 1;
//    found[num_found] = 30;
//    num_found = num_found + 1;
//    found[num_found] = 25;
//    num_found = num_found + 1;
//    found[num_found] = 24;
//    num_found = num_found + 1;
//    found[num_found] = 21;
//    num_found = num_found + 1;
//    found[num_found] = 26;
//    num_found = num_found + 1;
//    found[num_found] = 27;
//    num_found = num_found + 1;
//
//    /* update not_found use found */
//    for (a = 0; a < num_found; a++) {
//        for (b = 0; b < FILE_SIZE_6 / 32; b++) {
//            if(not_found[b] == (found[a] - 10 - 1) * 32){
//                for (c = b + 1; c < num_not_found; c++) {
//                    not_found[c - 1] = not_found[c];
//                }
//
//                not_found[num_not_found - 1] = -1;
//                num_not_found = num_not_found - 1;
//
//            }
//        }
//    }

    BYTE buf[SHA256_BLOCK_SIZE];

    BYTE password_guess[7];
    password_guess[6] = '\0';

    SHA256_CTX ctx;

    start = 0;
    finish = strlen(search);

    for (j = start; j < finish; j++){
        password_guess[0] = search[j];
        for (k = start; k < finish; k++){
            password_guess[1] = search[k];
            for (x = start; x < finish; x++){
                password_guess[2] = search[x];
                for (y = start; y < finish; y++){
                    password_guess[3] = search[y];
                    for (w = start; w < finish; w++){
                        password_guess[4] = search[w];
                        for (z = start; z < finish; z++){
                            password_guess[5] = search[z];
                            sha256_init(&ctx);
                            sha256_update(&ctx, password_guess, 6);
                            sha256_final(&ctx, buf);
                            for (i = 0; i < num_not_found; i++) {
                                /* compare password_guess with all hashes, and update found and not_found */
                                if (!memcmp(buffer + not_found[i], buf, SHA256_BLOCK_SIZE)){
                                    num_password = not_found[i]/32 + 1 + 10;
//                                    found[num_found] = num_password;
                                    num_found = num_found + 1;
                                    printf("%s %d\n",password_guess, num_password);

                                    for (b = 0; b < FILE_SIZE_6 / 32; b++) {
                                        if(not_found[b] == (num_password - 10 - 1) * 32){
                                            for (c = b + 1; c < num_not_found; c++) {
                                                not_found[c - 1] = not_found[c];
                                            }
                                            not_found[num_not_found - 1] = -1;
                                            num_not_found = num_not_found - 1;
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

/* print num_guesses of guesses of password */
void one_argument(int num_guesses) {
    int count, start, finish;
    int j, k, x, y, w, z;
    /* pf */
    char *search = "esionuta5lcd^r41zphg2ykb6wfYSPCA9*";
//    char *search = "eEaArRoOnNiIsStTlLcCdDmMhHgGbBuUpP1yYkKfFwW2vVjJ3zZ04596xX78qQ*?.-+&\\;\'!";

    BYTE password_guess[7];
    password_guess[6] = '\0';

    count = 0;
    start = 0;
    finish = strlen(search);

    for (j = start; j < finish; j++) {
        password_guess[0] = search[j];
        for (k = start; k < finish; k++) {
            password_guess[1] = search[k];
            for (x = start; x < finish; x++) {
                password_guess[2] = search[x];
                for (y = start; y < finish; y++) {
                    password_guess[3] = search[y];
                    for (w = start; w < finish; w++) {
                        password_guess[4] = search[w];
                        for (z = start; z < finish; z++) {
                            password_guess[5] = search[z];
                            printf("%s\n",password_guess);
                            count++;
                            if (count == num_guesses) {
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
}

/* guess hashed password in hash file using passwords in password_file */
void two_argument(char *password_file_name, char *hash_file_name){
    char *buffer;
    int hash_file_len;

    buffer = read_hash_file(hash_file_name);
    hash_file_len = hash_file_length(hash_file_name);

    SHA256_CTX ctx;
    BYTE buf[SHA256_BLOCK_SIZE];
    FILE *fp;
    char *password = NULL;
    int i, j;
    fp = fopen(password_file_name, "r");

    BYTE text[1000000];



    while(1) {
        if(feof(fp))
            break;
        password = get_line(fp);

        for (j = 0; j < strlen(password); j++) {
            text[j] = password[j];
        }
        text[strlen(password)] = '\0';

        sha256_init(&ctx);
        sha256_update(&ctx, text, strlen(password));
        sha256_final(&ctx, buf);
        for (i = 0; i < hash_file_len; i = i + 32) {
            if (!memcmp(buffer+i, buf, SHA256_BLOCK_SIZE)){
                printf("%s %d\n",text, i/32+1);
                break;
            }
        }
        free(password);
    }
    fclose(fp);
}

int main(int argc, char ** argv)
{
    /* call function according to number of argument input */
    if (argc == 1){
        four();
        six();
    } else if (argc == 2) {
        int num_guesses;
        num_guesses = atoi(argv[1]);
        one_argument(num_guesses);
    } else if (argc == 3) {
        two_argument(argv[1], argv[2]);
    }
}
