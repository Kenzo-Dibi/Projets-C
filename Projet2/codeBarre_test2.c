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

/**
 * \fn static void test__set_magicnumber1_(void)
 *
 * \brief tests different functions of the program
 */
static void test__set_magicnumber1_(void){

 PNM* qrcode = set_magicnumber(create_pnm(), P1);

 assert_true(qrcode);
 assert_int_equal(P1, get_magic_number(qrcode));

 set_magicnumber(qrcode, P2);
 assert_int_equal(P2, get_magic_number(qrcode));

 set_magicnumber(qrcode, P3);
 assert_int_equal(P3, get_magic_number(qrcode));

}//end test_create_pnm1

/**
 * \fn static void test__set_magicnumber2_(void)
 *
 * \brief tests different functions of the program
 */
static void test__set_magicnumber2_(void){

 PNM* qrcode = set_magicnumber(create_pnm(), P1);

 assert_true(qrcode);
 assert_int_equal(P1, get_magic_number(qrcode));

 set_magicnumber(qrcode, P2);
 assert_int_equal(P2, get_magic_number(qrcode));

 set_magicnumber(qrcode, P3);
 assert_int_equal(P3, get_magic_number(qrcode));

}//end test_create_pnm1

/**
 * \fn static void test_create_qrcode1(void)
 *
 * \brief tests different functions of the program
 */
static void test_create_pnm2(void){

    PNM* qrcode = set_lines_columns(create_pnm(), SIZE_MINI_MATRIX);
    assert_true(qrcode);

    assert_int_equal(SIZE_MINI_MATRIX, get_lines(qrcode));
    assert_int_equal(SIZE_MINI_MATRIX, get_columns(qrcode));

}//end create_pnm2
