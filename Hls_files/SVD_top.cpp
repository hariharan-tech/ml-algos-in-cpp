#include <stdio.h>
#include "SVD.hpp"
#include "SVD_top.h"

void svd(const float a_in[DIM*DIM],float eigval_op[DIM*DIM],float eigvec_op[DIM*DIM])
{

  float rot_matrix[DIM*DIM],rot_matrix_t[DIM*DIM];
  float temp[DIM*DIM],eigvec[DIM*DIM],a[DIM*DIM];
  READ_A_LOOP:for(int i=0;i<DIM*DIM;i++){
	  a[i] = a_in[i];
  }

  //Initialize Eigen Vector matrix
  INIT_R0: for(int r=0; r<DIM ;r++)
   INIT_C0: for(int c=0;c<DIM; c++)
       eigvec[r*DIM+c] = c==r?1:0 ;

  int row,col;
  float prec;
  non_diag_sum<DIM>(a,&prec);
  ITER_LOOP: for(int i=0;prec>PRECISION;i++)
  {
	  printf("%d",i);
      non_diag_max<DIM>(a,&row,&col);
      rot_init<DIM>(row,col,a,rot_matrix,rot_matrix_t);
      matrix_mul<DIM>(rot_matrix,a,temp);
      matrix_mul<DIM>(temp,rot_matrix_t,a);

      matrix_mul<DIM>(rot_matrix,eigvec,temp);

      //Reassign Eigen vector Matrix

      ITER_I_EIGVEC_WRITE: for (int index=0;index < DIM*DIM; index++)
          eigvec[index]=temp[index];

      non_diag_sum<DIM>(a,&prec);
  }
  WRITE_LOOP:for(int i=0;i<DIM*DIM;i++){
	  eigval_op[i] = a[i];
	  eigvec_op[i] = eigvec[i];
  }
}

//void svd(float a[DIM*DIM],float eigvec[DIM*DIM])
//{
//  float rot_matrix[DIM*DIM],rot_matrix_t[DIM*DIM];
//  float temp[DIM*DIM];
//
//  //Initialize Eigen Vector matrix
//  INIT_R0: for(int r=0; r<DIM ;r++)
//   INIT_C0: for(int c=0;c<DIM; c++)
//       eigvec[r*DIM+c] = c==r?1:0 ;
//
//  int row,col;
//  float prec;
//  non_diag_sum<DIM>(a,&prec);
//  ITER_LOOP: for(int i=0;prec>PRECISION;i++)
//  {
//      non_diag_max<DIM>(a,&row,&col);
//      rot_init<DIM>(row,col,a,rot_matrix,rot_matrix_t);
//      matrix_mul<DIM>(rot_matrix,a,temp);
//      matrix_mul<DIM>(temp,rot_matrix_t,a);
//
//      matrix_mul<DIM>(rot_matrix,eigvec,temp);
//
//      //Reassign Eigen vector Matrix
//
//      ITER_I_EIGVEC_WRITE: for (int index=0;index < DIM*DIM; index++)
//          eigvec[index]=temp[index];
//
//      non_diag_sum<DIM>(a,&prec);
//  }
//}
