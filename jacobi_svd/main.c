#include<stdio.h>
#include<math.h>

// TODO: Have to benchmark the resource util. of loop and hardcode matrix multiplication impl.
extern void matrix_2x2_mul_loop(float* mat1,float* mat2, float* op_mat){
    // 2x2 matrix multiplication using Loops
    // Check EPFL video for reference on HLS optimizations
    float prod[4] = {0.0};
    for(int k=0;k<2;k++){
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                prod[2*i+k] += mat1[2*i+j]*mat2[2*j+k]; // !!!!!
                // printf("arr[%d] += a[%d]*b[%d]\n",(2*i+k),(2*i+j),(2*j+k));
            }
        }
    }

    // Write the output
    for(int i=0;i<4;i++) op_mat[i] = prod[i];
}

extern void matrix_2x2_mul_hc(float* mat1, float* mat2, float* op_mat){
    // Hardcoded 2x2 matrix multiplication implementation
    op_mat[0] = mat1[0]*mat2[0] + mat1[1]*mat2[2];
    op_mat[1] = mat1[0]*mat2[1] + mat1[1]*mat2[3];
    op_mat[2] = mat1[2]*mat2[0] + mat1[3]*mat2[2];
    op_mat[3] = mat1[2]*mat2[1] + mat1[3]*mat2[3];
}

extern void transpose2x2(float* ip_mat, float* op_mat){
    op_mat[0] = ip_mat[0];
    op_mat[3] = ip_mat[3];
    op_mat[1] = ip_mat[2];
    op_mat[2] = ip_mat[1];
}

extern void eigenval_vec(float* input_mat, float* eigenvalues, float* eigenvectors){
    // Uses Jacobi Eigenvalue algorithm
    // returns a 2x2 SP Floating point matrix with eigen values in 1D forms
    // Accepts the input matrix, location in memory to store eigenvalues and eigenvectors
    
    // Store the input matrix locally
    float a[4], T, tan_min, sin_rot, cos_rot,temp1[4],eig_vec[4],temp2[4],eig_val[4];
    for(int i=0;i<4;i++) a[i] = input_mat[i]; // Optimize this using loop unroll

    // Find the value T = (a11-a22)/(2*a12)
    T = (a[0]-a[3])/(2*a[1]);

    // Find the tan(rot_angle)
    // There are 2 solutions, and we select one as per the value of T
    // Select t which is minimum
    if(T>=0) tan_min = 1/(T+sqrtf(1+T*T)); // We need to try to optimize this (seems high hardware intensive)
    else tan_min = 1/(T-sqrtf(1+T*T));

    // Now find cosine and sine of the rotation angle
    cos_rot = 1/sqrtf(1+tan_min*tan_min);
    sin_rot = cos_rot*tan_min;

    // Now this rotation matrix is the transpose of normalized eigenvector
    temp1[0] = cos_rot; temp1[1] = sin_rot;
    temp1[2] = -sin_rot; temp1[3] = cos_rot;

    // Finding R'AR to get eigenvalues!
    transpose2x2(temp1,eig_vec); // Storing the eigenvector first (using Transpose of temp1)
    matrix_2x2_mul_loop(a,eig_vec,temp2); // Performing matmul of A and R, storing in temp2
    matrix_2x2_mul_loop(temp1,temp2,eig_val); // Performing matmul of temp1 and temp2, storing in eig_val

    for(int i=0;i<4;i++){
        eigenvalues[i] =eig_val[i]; // Writing eigenvalues to the ports
        eigenvectors[i] = eig_vec[i]; // Writing eigenvectors to the ports
    }
}

void test_eigen(){
    float input_mat[4] = {8.0,2.0,2.0,4.0}, eigen_vals[4], eigen_vec[4];
    eigenval_vec(&input_mat,&eigen_vals,&eigen_vec);
    printf("The eigenvalues are: %f %f\nThe eigenvector is\n",eigen_vals[0],eigen_vals[3]);
    for(int i=0;i<4;i++){
        printf("%f\t",eigen_vec[i]);
        if(i==1) printf("\n\n");
    }
}

void test_matmul2x2_loop(){
    float mat1[4] = {1.0,2.0,2.0,1.0}, mat2[4] = {1.0,1.0,0.0,1.0}, op_mat[4];
    matrix_2x2_mul_loop(&mat1,&mat2,&op_mat);
    for(int i=0;i<4;i++){
        printf("%f\t",op_mat[i]);
        if(i==1) printf("\n");
    }
}

void test_matmul2x2_hc(){
    float mat1[4] = {1.0,2.0,2.0,1.0}, mat2[4] = {1.0,1.0,0.0,1.0}, op_mat[4];
    matrix_2x2_mul_hc(&mat1,&mat2,&op_mat);
    for(int i=0;i<4;i++){
        printf("%f\t",op_mat[i]);
        if(i==1) printf("\n");
    }
}