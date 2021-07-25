#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "dense_layer.h"
#include "activation_layer.h"

#define ARRAYSIZE(a) (sizeof(a) / sizeof(a[0]))

struct DenseLayer layers[100];
struct ActivationLayer alayers[100];

double mse(double y_true, double y_pred){
    return pow(y_true-y_pred, 2);
}

double mse_prime(double y_true, double y_pred){
    return 2*(y_pred-y_true);
}


struct Network{
    int num_layers;
};

void init_Network(struct Network *NN){
    NN->num_layers = 0;
}

void addlayer(struct Network *NN, int input_size, int output_size){
    struct DenseLayer new_layer;
    struct ActivationLayer new_alayer;
    init_DenseLayer(&new_layer, input_size, output_size);
    layers[NN->num_layers] = new_layer;
    alayers[NN->num_layers] = new_alayer;
    NN->num_layers++;
}

void fit(struct Network *NN, double X_train[][3], double y_train[],int epochs,int learning_rate){
    int samples = 3;
    for(int eno=0;eno<epochs;eno++){
        double err = 0;
        for(int i=0;i<samples;i++){
            double output[1000] = {0};    
            for(int j=0;j<ARRAYSIZE(X_train[0]);j++){
                output[i] = X_train[i][j];
            }
            for(int j=0;j<NN->num_layers;j++){
                double *op = forward_propogation(&layers[j], output);
                double *op1 = act_forward_propogation(&alayers[j], op, layers[j].output_size);
                for(int k=0; k< layers[j].output_size; k++){
                    output[k] = op1[k];
                }
                free(op);
                free(op1);
            } 
            err += mse(y_train[i], output[0]);
            double error = mse_prime(y_train[i], output[0]);
            double aerror[100];
            aerror[0] = error;
            for(int j=NN->num_layers-1;j>=0;j--){
                double *op2 = act_backward_propogation(&alayers[j], aerror, layers[j].output_size ,0.001);
                double *op3 = backward_probogation(&layers[j], op2, 0.1);
                for(int k=0; k< layers[j].output_size; k++){
                    aerror[k] = op3[k];
                }
                free(op2);
                free(op3);
            }
        }
        err /= samples;
        printf("Epoch %d/%d  Error=%g\n",eno+1,epochs,err);
    }
}

double *predict(struct Network *NN, double X_train[][3]){
    int samples = 3;
    double *outputs = (double *)malloc(sizeof(double *) * 1000);
    int counter=0;
        for(int i=0;i<samples;i++){
            double output[1000] = {0};    
            for(int j=0;j<ARRAYSIZE(X_train[0]);j++){
                output[i] = X_train[i][j];
            }

            for(int j=0;j<NN->num_layers;j++){
                double *op = forward_propogation(&layers[j], output);
                double *op1 = act_forward_propogation(&alayers[j], op, layers[j].output_size);
                for(int k=0; k< layers[j].output_size; k++){
                    output[k] = op1[k];
                }
                free(op);
                free(op1);
            } 
            outputs[counter] = output[0];
            counter++;
        }
    return outputs;
}

int main(){
    struct Network network;
    init_Network(&network);
    addlayer(&network, 3, 5);
    addlayer(&network, 5, 1);
    for(int i=0;i<network.num_layers;i++){
        printf("layer no. %d INP: %d OP: %d\n", i, layers[i].input_size, layers[i].output_size);
    }
    double X_train[3][3] = {{1,1,1}, {0,0,0}, {1,0,1}};
    double y_train[3] = {1,0,1};
    fit(&network, X_train, y_train, 100, 0.1);
    double *predictions = predict(&network, X_train);
    printf("\nPredictions: \n");
    for(int i=0;i<3;i++){
        printf("%g ", predictions[i]);
    }
    printf("\n");
}