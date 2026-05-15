#define SIZE 10000
typedef int BaseType;
void matrix_vector_mult_unopt(BaseType M[SIZE][SIZE], BaseType V_In[SIZE],
                              BaseType V_Out[SIZE]) {
    
                                
    BaseType i, j;

    BaseType sumLoop[SIZE]; //Maybe
    #pragma HLS ARRAY_PARTITION variable=sumLoop complete

    data_loop:
    for (i = 0; i < SIZE; i++) {
        #pragma HLS PIPELINE off
        BaseType sum = 0;
        dot_product_loop:
        for (j = 0; j < SIZE; j++) {
            #pragma HLS UNROLL
            sum += V_In[j] * M[i][j];
        }
        
        for(j=0; j< SIZE; j++){
            #pragma HLS UNROLL
            sum+=sumLoop[j];
        }
        
        V_Out[i] = sum;
    }
}