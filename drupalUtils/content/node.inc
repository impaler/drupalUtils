<?php

/**
 * Create a new node_content entity based on a settings array
 * Include images id array to attach file fields
 *
 * @param array $settings
 *
 * @return bool
 */
function createNode ( array $settings ) {
////    example
//    $node = array (
//        'title' => 'Node Title' ,
//        'type' => 'page' ,
//        'path' => 'pathalias' ,
//        'uid' => 1 ,
//    );
//    $node = create_node ( $node );

    //prepare standard settings
    $node = new stdClass();
    $node->type = $settings[ 'type' ];
    $node->bundle = 'node_content';
    $node->title = $settings[ 'title' ];
    $node->language = LANGUAGE_NONE;
    node_object_prepare ( $node );

    //setup more settings
    $node->custom = TRUE;
    $node->modified = TRUE;
    $node->locked = FALSE;
    $node->status = 1;
    $node->active = 1;
    $node->promote = 1;

    if ( isset ( $settings[ 'path' ] ) ) {
        $node->path = array (
            'alias' => $settings[ 'path' ]
        );
    } else {
        $node->path[ 'pathauto' ] = TRUE;
    }

    //make sure right user is being used in drush
    global $user;
    if ( empty ( $settings[ 'uid' ] ) ) {
        if ( $user->uid == 0 ) {
            $node->uid = 1;
        } else {
            $node->uid = $user->uid;
        }
    } else {
        $node->uid = $settings[ 'uid' ];
    }

    // Set the timestamp fields.
    if ( empty( $settings[ 'created' ] ) )
        $node->created = $settings[ 'created' ];

    if ( empty( $settings[ 'changed' ] ) )
        $node->changed = $settings[ 'changed' ];

    if ( ! empty( $settings[ 'timestamp' ] ) )
        $node->timestamp = $settings[ 'timestamp' ];

    node_save ( $node );

}
