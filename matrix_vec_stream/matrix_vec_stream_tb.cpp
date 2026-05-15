
#include "ap_axi_sdata.h"
#include "hls_stream.h"
#include <iostream>

using namespace std;
#define SIZE 10
typedef int BaseType;
typedef ap_axis<32, 2, 5, 8> axis_data;
void matrix_vec_stream(hls::stream<axis_data> &in_M,
                       hls::stream<axis_data> &in_V,
                       hls::stream<axis_data> &out);
int main(int argc, char *argv[]) {
  int input_arr[SIZE * SIZE];
  int input_vec[SIZE];
  int output_arr[SIZE];
  
  hls::stream<axis_data> in_M;
  hls::stream<axis_data> in_V;
  hls::stream<axis_data> out;
  
  //Load Matrix Data
  for (int i = 0; i < (SIZE * SIZE); i++) {
    axis_data tmp;
    tmp.data = i;
    tmp.user = 0;
    tmp.last = (i == SIZE * SIZE - 1);
    in_M.write(tmp);
  }

  //Load Vector Data
  for(int i = 0; i < (SIZE); i++){
    axis_data tmp;
    tmp.data = i;
    tmp.user = 0;
    tmp.last = (i == SIZE * SIZE - 1);
    in_V.write(tmp);
  }
  
  //Run Program
  matrix_vec_stream(in_M, in_V, out);

  //Stream data out
  cout << "===== matrix_vec_stream results =====" << endl;
  for (int i = 0; i < (SIZE); i++) {
    axis_data tmp = out.read();
    cout << tmp.data << " ";
  }
  cout << endl;
   cout << "=====================================" << endl;
  
  return 0;
}
