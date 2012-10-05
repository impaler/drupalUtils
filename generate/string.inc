<?php

/**
 * Generates a random string of ASCII characters of codes 32 to 126.
 *
 * The generated string includes alpha-numeric characters and common misc
 * characters. Use this method when testing general input where the content
 * is not restricted.
 *
 * @param int $length
 * @internal param Length $int $length Length of random string to generate.
 *
 * @return Randomly generated string.
 */
function getRandomString ( $length = 8 ) {
    $str = '';
    for ( $i = 0 ; $i < $length ; $i ++ ) {
        $str .= chr ( mt_rand ( 32 , 126 ) );
    }
    return $str;
}

/**
 * Generates a random string containing letters and numbers.
 *
 * The string will always start with a letter. The letters may be upper or
 * lower case. This method is better for restricted inputs that do not
 * accept certain characters. For example, when testing input fields that
 * require machine readable values (i.e. without spaces and non-standard
 * characters) this method is best.
 *
 * @param int $length
 * @internal param \Length $int $length Length of random string to generate.
 *
 * @return Randomly generated string.
 */

function getRandomName ( $length = 8 ) {
    $values = array_merge ( range ( 65 , 90 ) , range ( 97 , 122 ) , range ( 48 , 57 ) );
    $max = count ( $values ) - 1;
    $str = chr ( mt_rand ( 97 , 122 ) );
    for ( $i = 1 ; $i < $length ; $i ++ ) {
        $str .= chr ( $values[ mt_rand ( 0 , $max ) ] );
    }
    return $str;
}

function getHTMLContent ( $length = 100 ) {
    require_once( 'lorem_ipsum.inc' );
    $generator = new lorem_ipsum;
    
    return $generator->getContent ( $length );
}