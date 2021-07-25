#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define ARRAYSIZE(a) (sizeof(a) / sizeof(a[0]))

struct DenseLayer {
    int input_size;
    int output_size;

    double weights[1000][1000];
    double bias[1][1000];
    double input[1000];
    double output[1000];
};

void forward_propogation(struct DenseLayer* DL,double input_data[]){
    for(int i=0;i<DL->input_size;i++) {
        DL->input[i]=input_data[i];
    }
    for(int i=0;i<DL->output_size;i++){
        double sum = 0;
        for(int j=0;j<DL->input_size;j++){
            sum += DL->weights[i][j]*DL->input[j];
        }
        DL->output[i] = sum + DL->bias[0][i];
    }

}

double *backward_probogation(struct DenseLayer* DL,double output_error[], double learning_rate){
    int input_size = DL->input_size;
    int output_size = DL->output_size;
    double *input_error = (double *)malloc(sizeof(double *) * input_size);
    double weights_error[input_size][output_size];
    for(int i=0; i< input_size; i++){
        double sum = 0;
        for(int j=0;j<output_size;j++){
            sum += DL->weights[i][j]*output_error[j];
        }
        input_error[i] = sum;
    }
    for(int i=0;i<input_size;i++){
        for(int j=0;j<output_size; j++){
            weights_error[i][j] = DL->input[i]*output_error[j];
        }
    }

    for(int i=0;i<output_size;i++){
        for(int j=0;j<input_size;j++){
            DL->weights[i][j] -= learning_rate*weights_error[j][i];
        }
    }
    for(int i=0;i<output_size;i++){
        DL->bias[0][i] -= learning_rate*output_error[i];
    }

    return input_error;
}



void init_DenseLayer(struct DenseLayer* DL, int input_size, int output_size){
    DL->input_size = input_size;
    DL->output_size = output_size;
    for(int i=0; i<output_size; i++){
        for(int j=0; j<input_size; j++){
            DL->weights[i][j] = (rand() / (double)RAND_MAX)-0.5;
            if(i==0){
                DL->bias[0][j] = (rand() / (double)RAND_MAX)-0.5;
            }
        }
    }    
}