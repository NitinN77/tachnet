#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "dense_layer.h"
#include "activation_layer.h"

struct DenseLayer layers[100];

struct Network{
    int num_layers;
};

void init_Network(struct Network *NN){
    NN->num_layers = 0;
}

void addlayer(struct Network *NN, int input_size, int output_size){
    struct DenseLayer new_layer;
    init_DenseLayer(&new_layer, input_size, output_size);
    layers[NN->num_layers] = new_layer;
    NN->num_layers++;
}

int main(){
    struct Network network;
    init_Network(&network);
    addlayer(&network, 3, 5);
    addlayer(&network, 5, 1);
    for(int i=0;i<network.num_layers;i++){
        printf("layer no. %d INP: %d OP: %d\n", i, layers[i].input_size, layers[i].output_size);
    }
}