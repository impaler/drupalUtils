<?php

/**
 * Get random elements from an array
 *
 * @param $array
 * @param int $min
 * @param int $max
 * @internal param int $min
 * @return array
 */
function randArraySelection ( $array , $min = 1 , $max = 1 ) {
    if ( $max == 1 && $max == 1 ) {
        $selection = array_rand ( $array , 1 );
        $return = $array[ $selection ];
    } else {
        $amount = rand ( $min , $max );
        $selection = array_rand ( $array , $amount );

        foreach ( $selection as $key => $value ) {
            $return[ ] = $array[$key];
        }
    }
    return $return;
}