<?php

/**
 * Private function for Pathauto to create an alias.
 *
 * @param $path
 */
function createPathAlias($path) {
    ////    example
    //$path = array(
    //  'source' => 'node/4',
    //  'alias' => 'explore',
    //  'language' => 'und',
    //);
    //createPathAlias($path);
    module_load_include("inc", 'pathauto' );
    _pathauto_set_alias( $path );
}
