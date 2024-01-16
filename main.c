#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#define PI 3.14159265359

typedef struct
{
    float real;
    float imag;
}complex;


void PrintOut(complex num, float f);
complex Division(complex x, complex y);
complex func1(float R, float C, float L, float f);
complex func2(float R, float C, float L, float f);
complex func3(float R1, float R2, float C, float L, float f);
complex func4(float R1, float R2, float C, float L, float f);
float CheckValue(char *prompt, char special);


int main() {
    complex y;
    complex x;
    float R1, R2, L, C, w, f, fmin, fmax, df;

    int choice;

    while(1){
        printf("Please, enter the choice 1-4: ");
        scanf("%d", &choice);

        while(choice != 1 && choice != 2 && choice != 3 && choice != 4){
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Please, reenter: ");
            scanf("%d", &choice);

        }

        if(choice == 3 || choice == 4){
            R1 = CheckValue("Enter R1: ", ' ');
            R2 = CheckValue("Enter R2: ", ' ');

        }
        else{
            R1 = CheckValue("Enter R: ", ' ');
        }

        while(1){
            L = CheckValue("Enter L: ", ' ');
            C = CheckValue("Enter C: ", ' ');
            f = 1.0/(2*PI*sqrt(L*C));
            if(!isinf(f) && !isnan(f)){
                break;
            }
            else{
                printf("Please, reenter L and C. They must be greater than zero\n");
            }
        }

        printf("Current f: %fHz\n", f);
        while(1){
            fmin = CheckValue("Enter fmin (Hz): ", ' ');
            fmax = CheckValue("Enter fmax (Hz): ", ' ');
            if(fmin > f || fmax < f){
                printf("f lies outside this scope. Reenter.\n");
            }
            else{
                break;
            }
        }

        df = CheckValue("Enter df: ", 'D');
        printf("\n");


        switch (choice){
            case 1:
                while(f>= fmin && f<=fmax){
                    if (df == 0){
                        PrintOut(func1(R1,C, L, f), f);
                        break;
                    }
                    PrintOut(func1(R1,C, L, f), f);
                    f+= df;

                }
                break;

            case 2:
                while(f>= fmin && f<=fmax){
                    if (df == 0){
                        PrintOut(func2(R1,C, L, f), f);
                        break;
                    }
                    PrintOut(func2(R1,C, L, f), f);
                    f+= df;

                }
                break;
            case 3:
            while(f>= fmin && f<=fmax){
                    if (df == 0){
                        PrintOut(func3(R1,R2, C, L, f), f);
                        break;
                    }
                    PrintOut(func3(R1,R2, C, L, f), f);
                    f+= df;

                }
                break;
            case 4:
                while(f>= fmin && f<=fmax){
                    if (df == 0){
                        PrintOut(func4(R1,R2, C, L, f), f);
                        break;
                    }
                    PrintOut(func4(R1,R2, C, L, f), f);
                    f+= df;

                }
                break;

        }

        int c;
        char answer = ' ';
        
        while ((c = getchar()) != '\n' && c != EOF);

        while(answer != 'N' && answer != 'Y'){
            printf("\nWould you like to continue? Y/N: ");
            scanf("%c", &answer);
            while ((c = getchar()) != '\n' && c != EOF);
        }
        if(answer == 'Y'){
            printf("\n");
        }
        else if (answer == 'N'){

            break;
        }

    }
    


    getchar();

    return 0;
}



complex func1(float R, float C, float L, float f){
    complex x, y;
    float w = 2*PI*f;
    x.real = L/C;
    x.imag = -R/(w*C);
    y.real = R;
    y.imag = w*L - 1.0/(w*C);
    return Division(x, y);
}

complex func2(float R, float C, float L, float f){
    complex x, y;
    float w = 2*PI*f;
    x.real = L/C;
    x.imag = R/(w*C);
    y.real = R;
    y.imag = w*L - 1.0/(w*C);
    return Division(x, y);

}
complex func3(float R1, float R2, float C, float L, float f){
    complex x, y;
    float w = 2*PI*f;
    x.real = R1*R2;
    x.imag = R1*(w*L - 1.0/(w*C));
    y.real = R1 + R2;
    y.imag = w*L - 1.0/(w*C);
    return Division(x, y);

}
complex func4(float R1, float R2, float C, float L, float f){
    complex x, y;
    float w = 2*PI*f;
    x.real = R1*R2 + L/C;
    x.imag = R1*(w*L*R1 - R2/(w*C));
    y.real = R1 + R2;
    y.imag = w*L - 1.0/(w*C);
    return Division(x, y);

}
complex Division(complex x, complex y){
    complex result;
    result.real = (x.real * y.real + x.imag * y.imag)/(y.real * y.real + y.imag * y.imag);
    result.imag = (x.imag * y.real - x.real * y.imag)/(y.real * y.real + y.imag * y.imag);
    return result;
}

void PrintOut(complex num, float f){
    if(num.imag < 0){
        printf("Current Z is %f - %fi at f = %fHz\n", num.real, -num.imag, f);
    }
    else{
        printf("Current Z is %f + %fi at f = %fHz\n", num.real, num.imag, f);
    }

}

float CheckValue(char *prompt, char special){
    char buffer[100];

    printf("%s", prompt);
    while(1){
        int checkI = 1;
        scanf("%99s", buffer);
        for(int i = 0; buffer[i]; i++){
            if (isdigit(buffer[i]) == 0 && buffer[i] != '.' && buffer[i] && special != 'D')
            {
                printf("\nYour input is invalid. Negative values not allowed. Reenter: ");
                checkI = 0;
                break;
            }
            else if(isdigit(buffer[i]) == 0 && buffer[i] != '.' && buffer[i] && special == 'D' && buffer[i] != '-'){
                checkI = 0;
                break;
            }
        }
        if(checkI == 1){
            break;
        }
    }
    return atof(buffer);
}
