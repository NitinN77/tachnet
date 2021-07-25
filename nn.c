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

double *arrtanh(double arr[]){
    double *ret = (double *)malloc(sizeof(double *) * ARRAYSIZE(arr));
    for(int i=0; i<ARRAYSIZE(arr); i++){
        ret[i] = tanh(arr[i]);
    }
    return ret;
}

double *arrtanh_prime(double arr[]){
    double *ret = (double *)malloc(sizeof(double *) * ARRAYSIZE(arr));
    for(int i=0; i<ARRAYSIZE(arr); i++){
        ret[i] = 1-pow(tanh(arr[i]), 2);
    }
    return ret;
}


struct ActivationLayer{
    char *activation;  
    char *activation_prime;
    double input[1000];
    double output[1000];
};

void init_ActivationLayer(struct ActivationLayer* AL, char* activation, char* activation_prime){
    strcpy(AL->activation, activation);
    strcpy(AL->activation_prime, activation_prime);
}

void act_forward_propogation(struct ActivationLayer* AL, double input_data[]){
    printf("siez: %g\n", ARRAYSIZE(input_data));
    for(int i=0;i<ARRAYSIZE(input_data); i++){
        AL->input[i] = input_data[i];
    }
    double *temp = arrtanh(AL->input);
    for(int i=0;i<ARRAYSIZE(temp);i++){
        AL->output[i] = temp[i];
    }
}

double *act_backward_propogation(struct ActivationLayer* AL, double output_error[], double learning_rate){
    double *temp = arrtanh_prime(AL->input);
    double *ret = (double *)malloc(sizeof(double *) * ARRAYSIZE(temp));
    for(int i=0;i<ARRAYSIZE(temp); i++){
        ret[i] = temp[i] * output_error[i];
    }
    return ret;
}

int main(){
    struct DenseLayer l1;
    init_DenseLayer(&l1, 3, 5);
    for(int i=0; i<5; i++){
        for(int j=0; j<3; j++){
            printf("%g ", l1.weights[i][j]);
        }
        printf("\n");
    }     

    double samp[] = {2,2,2};
    forward_propogation(&l1, samp);
    for(int i=0;i<5;i++){
        printf("%g ", l1.output[i]);
    }

    printf("\n");
    double sampoperr[] = {4, 4, 2, 1, 2};
    double *err = backward_probogation(&l1, sampoperr, 0.01);
    for(int i=0;i<3;i++){
        printf("%g ",err[i]);
    }
    free(err);
    printf("\n");
    for(int i=0; i<5; i++){
        for(int j=0; j<3; j++){
            printf("%g ", l1.weights[i][j]);
        }
        printf("\n");
    }     

    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    struct ActivationLayer l2;
    double *ttemp = {2,3,4,1,5};
    printf("siez1: %g\n", sizeof(ttemp));
    double temp1[] = {6.3,6.1, 0.3, 5.2};
    act_forward_propogation(&l2, ttemp);
    for(int i=0;i<5;i++){
        printf("%g ", l2.output[i]);
    }
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    double *op = act_backward_propogation(&l2, temp1, 0.01);
    for(int i=0;i<5;i++){
        printf("%g ", op[i]);
    }
    printf("\n\n");
}

// class Layer:
//     def __init__(self):
//         self.input = None
//         self.output = None

//     # computes the output Y of a layer for a given input X
//     def forward_propagation(self, input):
//         raise NotImplementedError

//     # computes dE/dX for a given dE/dY (and update parameters if any)
//     def backward_propagation(self, output_error, learning_rate):
//         raise NotImplementedError