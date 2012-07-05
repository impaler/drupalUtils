<?php

/**
 * Create a new Node content Type
 *
 * @param array $settings
 *
 */
function createNodeContentType ( array $settings ) {
    /*
     * Example Usage
        $settings = array (
            'type'        => 'site_page' ,
            'name'        => 'Basic Site Page' ,
            'description' => "Use <em>site pages</em> for basic static page content." ,
        );

        createNodeContentType ( $settings );
    */

    // We define the node type as an associative array.
    $contentTypeData = array (
        'type' => $settings[ 'type' ] ,
        'name' => $settings[ 'name' ] ,
        'base' => 'node_content' ,
        'description' => $settings[ 'description' ] ,
        'custom' => FALSE ,
    );

    $contentType = node_type_set_defaults ( $contentTypeData );
    $contentType->custom = 0;
    $contentType->modified = 0;
    $contentType->locked = 0;

    variable_set ( 'comment_' . $settings[ 'type' ] , '1' );

    //core node type save
    node_type_save ( $contentType );

}
