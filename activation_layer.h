#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define ARRAYSIZE(a) (sizeof(a) / sizeof(a[0]))

double *arrtanh(double arr[], int n){
    double *ret = (double *)malloc(sizeof(double *) * n);
    for(int i=0; i<n; i++){
        ret[i] = tanh(arr[i]);
    }
    return ret;
}

double *arrtanh_prime(double arr[], int n){
    //printf("sioee: %d",ARRAYSIZE(arr));
    double *ret = (double *)malloc(sizeof(double *) *n);
    for(int i=0; i<n; i++){
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

void act_forward_propogation(struct ActivationLayer* AL, double input_data[], int n){
    for(int i=0;i<n; i++){
        AL->input[i] = input_data[i];
    }
    double *temp = arrtanh(AL->input, n);
    for(int i=0;i<n;i++){
        AL->output[i] = temp[i];
    }
}

double *act_backward_propogation(struct ActivationLayer* AL, double output_error[], int n, double learning_rate){
    double *temp = arrtanh_prime(AL->input, n);
    double *ret = (double *)malloc(sizeof(double *) * n);
    for(int i=0;i<n; i++){
        ret[i] = temp[i] * output_error[i];
    }
    return ret;
}