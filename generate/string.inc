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

function getRandomName ( $length = 2 ) {
    require_once( 'lorem_ipsum.inc' );
    $generator = new lorem_ipsum;
    
    return $generator->getContent($length, 'plain', false);
}

function getRandomHTMLContent ( $length = 100 ) {
    require_once( 'lorem_ipsum.inc' );
    $generator = new lorem_ipsum;
    
    return $generator->getContent ( $length );
}