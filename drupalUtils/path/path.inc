<?php

/**
 * Private function for Pathauto to create an alias.
 *
 * Eg;
$path = array(
'source' => 'node/4',
'alias' => 'explore',
'language' => 'und',
);
 *
 * @param $path
 */
function createPathAlias ( $path ) {
    module_load_include ( "inc" , 'pathauto' );
    _pathauto_set_alias ( $path );
}

