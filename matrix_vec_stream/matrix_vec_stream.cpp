#include "ap_axi_sdata.h"
#include "hls_stream.h"
#define SIZE 10000

typedef int BaseType;
typedef int64_t LargeSum;
typedef ap_axis<32, 2, 5, 8> axis_data;

//Two input streams: in_M
void matrix_vec_stream(hls::stream<axis_data> &in_M,
                       hls::stream<axis_data> &in_V,
                       hls::stream<axis_data> &out) {
                        
  // Map the parts of the AXIS protoco
  #pragma HLS INTERFACE axis port = in_M
  #pragma HLS INTERFACE axis port = in_V
  #pragma HLS INTERFACE axis port = out
  #pragma HLS INTERFACE s_axilite port = return bundle = CTRL
  
  //Data Structures and declaration
  BaseType V_In[SIZE];
  #pragma HLS ARRAY_PARTITION variable=V_In cyclic factor=16
  
  BaseType V_Out[SIZE];
  axis_data temp;
  BaseType i, j;
  BaseType M_temp;

  
  read_V_In_loop:
  for (j = 0; j < SIZE; j++) {
    #pragma HLS PIPELINE
    temp = in_V.read();
    V_In[j] = temp.data;
  }
    
  data_loop:
  for (i = 0; i < SIZE; i++) {
      LargeSum sum = 0;
    
    dot_product_loop:
    for (j = 0; j < SIZE; j++) {
      #pragma HLS PIPELINE
      M_temp = in_M.read().data;
      sum += V_In[j] * M_temp;

    }
    
    temp.data = sum;
    if (i == SIZE - 1)
      temp.last = 1;
    else
      temp.last = 0;
    out.write(temp);
  }
  
}
