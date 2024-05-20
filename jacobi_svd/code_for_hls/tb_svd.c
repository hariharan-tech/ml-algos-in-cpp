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

int main(){
    // Write test scripts here!
    return 0;
}