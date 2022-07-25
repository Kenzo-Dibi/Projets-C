/**
 * \file codebarre_test.c
 * 
 * \brief Ce fichier contient les définitions de types et les fonctions de créations de code barre.
 * 
 * \author: Dibi Kenzo s210122
 * \date: 4/04/2022
 * projet: INFO0030 Projet 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include "pnm.h"
#include "codeBarre.h"

#include "seatest.h"
#include "pnm.h"
#include "codeBarre.h"

#define SIZE_MATRIX 70

/**
 * \fn static void test_create_qrcode1(void)
 *
 * \brief tests different functions of the program
 */
static void test_create_qrcode1(void){
    PNM* qrcode = create_pnm();
    PNM* imageExemple;
    assert_false(generate_qrcode(&qrcode, "exemple/test1.txt", "exemple"));
    printf("coucou\n");
    assert_false(load_pnm(&imageExemple, "exemple/exemple.pbm"));
    assert_false(load_pnm(&qrcode, "exemple/87651234.pbm"));
    assert_int_equal(get_columns(imageExemple), get_columns(qrcode));
    assert_int_equal(get_lines(imageExemple), get_lines(qrcode));
    assert_int_equal(get_magic_number(imageExemple), get_magic_number(qrcode));

    for(unsigned i = 0; i < SIZE_MATRIX; i++){
        for(unsigned j = 0; j < SIZE_MATRIX; j++){
            assert_int_equal(get_value_matrix(imageExemple, i, j), get_value_matrix(qrcode, i, j));
        }// end for j
    }// end for i
    free_pnm(qrcode);
    qrcode = NULL;
    free_pnm(imageExemple);
    imageExemple = NULL;
}//end test_create_qrcode

/**
 * test_create_qrcode2
 *
 * tests letters detection
 */
static void test_create_qrcode2(void){
    PNM*qrcode = create_pnm();
    assert_int_equal(-1, generate_qrcode(&qrcode, "exemple/test2.txt", "exemple"));
    free_pnm(qrcode);
}// end test_create_qrcode2

/**
 * test_create_qrcode3
 *
 * tests empty lines detection
 */
static void test_create_qrcode3(void){
    
    PNM* qrcode = create_pnm();
    assert_int_equal(-1, generate_qrcode(&qrcode, "exemple/test3.txt", "exemple"));
    free_pnm(qrcode);
}//end test_create_qrcode2

/**
 * test_create_qrcode4
 *
 * tests the detection of invalid size number
 */
static void test_create_qrcode4(void){
    
    PNM* qrcode = create_pnm();
    assert_int_equal(-1, generate_qrcode(&qrcode, "exemple/test4.txt", "exemple"));
    free_pnm(qrcode);
}

/**
 * test_create_qrcode5
 *
 * tests the detection of negative number
 */
static void test_create_qrcode5(void){
    
    PNM* qrcode = create_pnm();
    assert_int_equal(-1, generate_qrcode(&qrcode, "exemple/test5.txt", "exemple"));
    free_pnm(qrcode);
}

/**
 * test_create_qrcode6
 *
 * tests the number 00000000 and 99999999
 */
static void test_create_qrcode6(void){
    PNM* qrcode = create_pnm();
    assert_false(generate_qrcode(&qrcode, "exemple/test6.txt", "exemple"));
    free_pnm(qrcode);
}
void test_fixture(){
    test_fixture_start();

    //run_test(test_create_qrcode1);
    run_test(test_create_qrcode2);
    run_test(test_create_qrcode3);
    run_test(test_create_qrcode4);
    run_test(test_create_qrcode5);
    run_test(test_create_qrcode6);

    test_fixture_end();
}// end test_fixture

void all_tests(void){
    test_fixture();
}

int main(){
    return run_tests(all_tests);
}// end main